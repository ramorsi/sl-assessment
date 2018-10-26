#include "StreamLabsServer.h"

using namespace std;

#define BUFSIZE 512
#define DEFAULT_PIPE_NAME default_pipe_name

StreamLabsServer* StreamLabsServer::instance;

StreamLabsServer::StreamLabsServer() {}

int StreamLabsServer::initServer()
{
	BOOL   fConnected = FALSE;
	DWORD  dwThreadId = 0;
	HANDLE hPipe = INVALID_HANDLE_VALUE, hThread = NULL;
	//TODO make this dynamic with pipe name
	LPCTSTR lpszPipename = TEXT("\\\\.\\pipe\\streamlabs_pipe_name");

	// The main loop creates an instance of the named pipe and 
	// then waits for a client to connect to it. When the client 
	// connects, a thread is created to handle communications 
	// with that client, and this loop is free to wait for the
	// next client connect request. It is an infinite loop.

	for (;;)
	{
		_tprintf(TEXT("\nPipe Server: Main thread awaiting client connection on %s\n"), lpszPipename);
		hPipe = CreateNamedPipe(
			lpszPipename,             // pipe name 
			PIPE_ACCESS_DUPLEX,       // read/write access 
			PIPE_TYPE_MESSAGE |       // message type pipe 
			PIPE_READMODE_MESSAGE |   // message-read mode 
			PIPE_WAIT,                // blocking mode 
			PIPE_UNLIMITED_INSTANCES, // max. instances  
			BUFSIZE,                  // output buffer size 
			BUFSIZE,                  // input buffer size 
			0,                        // client time-out 
			NULL);                    // default security attribute 

		if (hPipe == INVALID_HANDLE_VALUE)
		{
			_tprintf(TEXT("CreateNamedPipe failed, GLE=%d.\n"), GetLastError());
			return -1;
		}

		// Wait for the client to connect; if it succeeds, 
		// the function returns a nonzero value. If the function
		// returns zero, GetLastError returns ERROR_PIPE_CONNECTED. 

		fConnected = ConnectNamedPipe(hPipe, NULL) ?
			TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

		if (fConnected)
		{
			printf("Client connected, creating a processing thread.\n");

			// Create a thread for this client. 
			hThread = CreateThread(
				NULL,              // no security attribute 
				0,                 // default stack size 
				InstanceThread,    // thread proc
				(LPVOID)hPipe,    // thread parameter 
				0,                 // not suspended 
				&dwThreadId);      // returns thread ID 

			if (hThread == NULL)
			{
				_tprintf(TEXT("CreateThread failed, GLE=%d.\n"), GetLastError());
				return -1;
			}
			else CloseHandle(hThread);
		}
		else
			// The client could not connect, so close the pipe. 
			CloseHandle(hPipe);
	}

	return 0;
}

DWORD WINAPI StreamLabsServer::InstanceThread(LPVOID lpvParam)
// This routine is a thread processing function to read from and reply to a client
// via the open pipe connection passed from the main loop. Note this allows
// the main loop to continue executing, potentially creating more threads of
// of this procedure to run concurrently, depending on the number of incoming
// client connections.
{
	HANDLE hHeap = GetProcessHeap();
	char* pchRequest = (char*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(char));
	char* pchReply = (char*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(char));

	//TCHAR* pchRequest = (TCHAR*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(TCHAR));
	//TCHAR* pchReply = (TCHAR*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(TCHAR));

	DWORD cbBytesRead = 0, cbReplyBytes = 0, cbWritten = 0;
	BOOL fSuccess = FALSE;
	HANDLE hPipe = NULL;

	// Do some extra error checking since the app will keep running even if this
	// thread fails.

	if (lpvParam == NULL)
	{
		printf("\nERROR - Pipe Server Failure:\n");
		printf("   InstanceThread got an unexpected NULL value in lpvParam.\n");
		printf("   InstanceThread exitting.\n");
		if (pchReply != NULL) HeapFree(hHeap, 0, pchReply);
		if (pchRequest != NULL) HeapFree(hHeap, 0, pchRequest);
		return (DWORD)-1;
	}

	if (pchRequest == NULL)
	{
		printf("\nERROR - Pipe Server Failure:\n");
		printf("   InstanceThread got an unexpected NULL heap allocation.\n");
		printf("   InstanceThread exitting.\n");
		if (pchReply != NULL) HeapFree(hHeap, 0, pchReply);
		return (DWORD)-1;
	}

	if (pchReply == NULL)
	{
		printf("\nERROR - Pipe Server Failure:\n");
		printf("   InstanceThread got an unexpected NULL heap allocation.\n");
		printf("   InstanceThread exitting.\n");
		if (pchRequest != NULL) HeapFree(hHeap, 0, pchRequest);
		return (DWORD)-1;
	}

	// Print verbose messages. In production code, this should be for debugging only.
	printf("InstanceThread created, receiving and processing messages.\n");

	// The thread's parameter is a handle to a pipe object instance. 

	hPipe = (HANDLE)lpvParam;

	// Loop until done reading
	while (1)
	{
		// Read client requests from the pipe. This simplistic code only allows messages
		// up to BUFSIZE characters in length.
		fSuccess = ReadFile(
			hPipe,        // handle to pipe 
			pchRequest,    // buffer to receive data 
			BUFSIZE * sizeof(TCHAR), // size of buffer 
			&cbBytesRead, // number of bytes read 
			NULL);        // not overlapped I/O 

		if (!fSuccess || cbBytesRead == 0)
		{
			if (GetLastError() == ERROR_BROKEN_PIPE)
			{
				_tprintf(TEXT("InstanceThread: client disconnected.\n"), GetLastError());
			}
			else
			{
				_tprintf(TEXT("InstanceThread ReadFile failed, GLE=%d.\n"), GetLastError());
			}
			break;
		}

		// Process the incoming message.
		StreamLabsServer::GetAnswerToRequest(pchRequest, pchReply, &cbReplyBytes);

		// Write the reply to the pipe. 
		fSuccess = WriteFile(
			hPipe,        // handle to pipe 
			pchReply,     // buffer to write from 
			cbReplyBytes, // number of bytes to write 
			&cbWritten,   // number of bytes written 
			NULL);        // not overlapped I/O 

		if (!fSuccess || cbReplyBytes != cbWritten)
		{
			_tprintf(TEXT("InstanceThread WriteFile failed, GLE=%d.\n"), GetLastError());
			break;
		}
	}

	// Flush the pipe to allow the client to read the pipe's contents 
	// before disconnecting. Then disconnect the pipe, and close the 
	// handle to this pipe instance. 

	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);

	HeapFree(hHeap, 0, pchRequest);
	HeapFree(hHeap, 0, pchReply);

	printf("InstanceThread exitting.\n");
	return 1;
}

VOID StreamLabsServer::GetAnswerToRequest(char* pchRequest,
	char* pchReply,
	LPDWORD pchBytes)
	// This routine is a simple function to print the client request to the console
	// and populate the reply buffer with a default data string. This is where you
	// would put the actual client request processing code that runs in the context
	// of an instance thread. Keep in mind the main thread will continue to wait for
	// and receive other client connections while the instance thread is working.
{
	_tprintf(TEXT("Client Request String:\"%s\"\n"), pchRequest);

	json requestJson = json::parse(pchRequest);
	int action = requestJson[ACTION];
	json requestArgs = requestJson[REQUEST_ARGS];
	switch (action)
	{
	case Action::CREATE_DUMMY_OBJECT:GetInstance()->CreateDummyObjectHandler(); break;
	case Action::DECREMENT_INTEGER:GetInstance()->DecrementIntegerHandler(requestArgs); break;
	case Action::GET_INTEGER:GetInstance()->GetIntegerHandler(requestArgs); break;
	case Action::GET_STRING:GetInstance()->GetStringHandler(requestArgs); break;
	case Action::INCREMENT_INTEGER:GetInstance()->IncrementIntegerHandler(requestArgs); break;
	case Action::REVERSE_STRING:GetInstance()->ReverseStringHandler(requestArgs); break;
	case Action::SET_INTEGER:GetInstance()->SetIntegerHandler(requestArgs); break;
	case Action::SET_STRING:GetInstance()->SetStringHandler(requestArgs); break;
	case Action::GET_OBJECT:GetInstance()->GetObjHandler(requestArgs); break;

	}

	// Check the outgoing message to make sure it's not too long for the buffer.
	if (FAILED(StringCchCopy((STRSAFE_LPWSTR)pchReply, BUFSIZE, TEXT("default answer from server"))))
	{
		*pchBytes = 0;
		pchReply[0] = 0;
		printf("StringCchCopy failed, no outgoing message.\n");
		return;
	}
	//*pchBytes = (lstrlen(pchReply) + 1) * sizeof(TCHAR);
	*pchBytes = (strlen(pchReply) + 1) * sizeof(TCHAR);
}

Response* StreamLabsServer::CreateDummyObjectHandler()
{
	return new Response(StatusCode::MY_SUCCESS) ;
}
Response* StreamLabsServer::DecrementIntegerHandler(json requestArgs)
{
	return new Response(StatusCode::MY_SUCCESS);
}
Response* StreamLabsServer::GetIntegerHandler(json requestArgs)
{
	return new Response(StatusCode::MY_SUCCESS);
}
Response* StreamLabsServer::GetStringHandler(json requestArgs){
	return new Response(StatusCode::MY_SUCCESS);
}
Response* StreamLabsServer::IncrementIntegerHandler(json requestArgs){
	DummyClass* dummy = new DummyClass();
	dummy->IncrementInteger();
	cout << "Dummy counter: " << dummy->GetInteger() << endl;
	dummy->IncrementInteger();
	cout << "Dummy counter again: " << dummy->GetInteger() << endl;
	return new Response(StatusCode::MY_SUCCESS);
}
Response* StreamLabsServer::ReverseStringHandler(json requestArgs) {
	return new Response(StatusCode::MY_SUCCESS);
}
Response* StreamLabsServer::SetIntegerHandler(json requestArgs) {
	return new Response(StatusCode::MY_SUCCESS);
}
Response* StreamLabsServer::SetStringHandler(json requestArgs) {
	return new Response(StatusCode::MY_SUCCESS);
}
Response* StreamLabsServer::GetObjHandler(json requestArgs) {
	return new Response(StatusCode::MY_SUCCESS);
}
