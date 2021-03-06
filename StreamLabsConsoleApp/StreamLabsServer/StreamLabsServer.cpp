#include "StreamLabsServer.h"

using namespace std;

StreamLabsServer* StreamLabsServer::instance;

StreamLabsServer::StreamLabsServer() {}
StreamLabsServer::~StreamLabsServer() {
	for (map<int, DummyClass*>::iterator itr = customObjects.begin(); itr != customObjects.end(); itr++)
	{
		delete (itr->second);
	}
}
int StreamLabsServer::StartServer()
{
	BOOL   fConnected = FALSE;
	DWORD  dwThreadId = 0;
	HANDLE hPipe = INVALID_HANDLE_VALUE, hThread = NULL;
	LPCWSTR lpszPipename = TEXT(PIPE_NAME);

	// The main loop creates an instance of the named pipe and 
	// then waits for a client to connect to it. When the client 
	// connects, a thread is created to handle communications 
	// with that client, and this loop is free to wait for the
	// next client connect request. It is an infinite loop.[Microsoft]

	for (;;)
	{
		_tprintf(TEXT("\nPipe Server: Main thread awaiting client connection on %s\n"), lpszPipename);
		hPipe = CreateNamedPipe(
			(LPCWSTR)lpszPipename,             // pipe name [Microsoft]
			PIPE_ACCESS_DUPLEX,       // read/write access [Microsoft] 
			PIPE_TYPE_MESSAGE |       // message type pipe [Microsoft]
			PIPE_READMODE_MESSAGE |   // message-read mode [Microsoft]
			PIPE_WAIT,                // blocking mode [Microsoft]
			PIPE_UNLIMITED_INSTANCES, // max. instances  [Microsoft]
			BUFSIZE,                  // output buffer size [Microsoft]
			BUFSIZE,                  // input buffer size [Microsoft]
			0,                        // client time-out [Microsoft]
			NULL);                    // default security attribute [Microsoft]

		if (hPipe == INVALID_HANDLE_VALUE)
		{
			_tprintf(TEXT("CreateNamedPipe failed, GLE=%d.\n"), GetLastError());
			return -1;
		}

		// Wait for the client to connect; if it succeeds, 
		// the function returns a nonzero value. If the function
		// returns zero, GetLastError returns ERROR_PIPE_CONNECTED. [Microsoft]

		fConnected = ConnectNamedPipe(hPipe, NULL) ?
			TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

		if (fConnected)
		{
			printf("Client connected, creating a processing thread.\n");

			// Create a thread for this client. [Microsoft]
			hThread = CreateThread(
				NULL,              // no security attribute [Microsoft] 
				0,                 // default stack size [Microsoft]
				InstanceThread,    // thread proc [Microsoft]
				(LPVOID)hPipe,    // thread parameter [Microsoft]
				0,                 // not suspended [Microsoft]
				&dwThreadId);      // returns thread ID [Microsoft] 

			if (hThread == NULL)
			{
				_tprintf(TEXT("CreateThread failed, GLE=%d.\n"), GetLastError());
				return -1;
			}
			else CloseHandle(hThread);
		}
		else
			// The client could not connect, so close the pipe. [Microsoft]
			CloseHandle(hPipe);
	}

	return 0;
}
// This routine is a thread processing function to read from and reply to a client
// via the open pipe connection passed from the main loop. Note this allows
// the main loop to continue executing, potentially creating more threads of
// of this procedure to run concurrently, depending on the number of incoming
// client connections. [Microsoft]
DWORD WINAPI StreamLabsServer::InstanceThread(LPVOID lpvParam)
{
	HANDLE hHeap = GetProcessHeap();
	char* pchRequest = (char*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(char));
	char* pchReply = (char*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(char));

	DWORD cbBytesRead = 0, cbReplyBytes = 0, cbWritten = 0;
	BOOL fSuccess = FALSE;
	HANDLE hPipe = NULL;

	// Do some extra error checking since the app will keep running even if this
	// thread fails. [Microsoft]

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

	printf("InstanceThread created, receiving and processing messages.\n");

	// The thread's parameter is a handle to a pipe object instance. [Microsoft]
	hPipe = (HANDLE)lpvParam;

	// Loop until done reading [Microsoft]
	while (1)
	{
		// Read client requests from the pipe. This simplistic code only allows messages
		// up to BUFSIZE characters in length. [Microsoft]
		fSuccess = ReadFile(
			hPipe,        // handle to pipe [Microsoft]
			pchRequest,    // buffer to receive data [Microsoft]
			BUFSIZE * sizeof(char), // size of buffer [Microsoft]
			&cbBytesRead, // number of bytes read [Microsoft]
			NULL);        // not overlapped I/O [Microsoft]

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

		// Process the incoming message. [Microsoft]
		Response response = StreamLabsServer::GetAnswerToRequest(pchRequest);
		cbReplyBytes = (strlen(response.ToString().c_str()) + 1) * sizeof(char);
		if (cbReplyBytes > BUFSIZE)
			throw StreamLabsException(StatusCode::MESSAGE_TOO_LONG);
		printf("Sending %d byte message: %s\n", cbReplyBytes, response.ToString().c_str());

		fSuccess = WriteFile(
			hPipe,                  // pipe handle [Microsoft]
			response.ToString().c_str(),  // message [Microsoft]
			cbReplyBytes,              // message length [Microsoft]
			&cbWritten,             // bytes written [Microsoft]
			NULL);                  // not overlapped [Microsoft]


		if (!fSuccess || cbReplyBytes != cbWritten)
		{
			_tprintf(TEXT("InstanceThread WriteFile failed, GLE=%d.\n"), GetLastError());
			break;
		}
	}

	// Flush the pipe to allow the client to read the pipe's contents 
	// before disconnecting. Then disconnect the pipe, and close the 
	// handle to this pipe instance. [Microsoft]

	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);

	HeapFree(hHeap, 0, pchRequest);
	HeapFree(hHeap, 0, pchReply);

	printf("InstanceThread exitting.\n");
	return 1;
}
Response StreamLabsServer::GetAnswerToRequest(char* requestStr)
{
	Response response = Response(StatusCode::MY_ERROR); 
	Request request = Request(requestStr);
	GetInstance()->LogRequest(request);
	int action = request.GetAction();
	json requestArgs = request.GetRequestArgs();
	try {
		switch (action)
		{
		case Action::CREATE_DUMMY_OBJECT: response = GetInstance()->CreateDummyObjectHandler(); break;
		case Action::DECREMENT_INTEGER:response = GetInstance()->DecrementIntegerHandler(requestArgs); break;
		case Action::GET_INTEGER:response = GetInstance()->GetIntegerHandler(requestArgs); break;
		case Action::GET_STRING:response = GetInstance()->GetStringHandler(requestArgs); break;
		case Action::INCREMENT_INTEGER:response = GetInstance()->IncrementIntegerHandler(requestArgs); break;
		case Action::REVERSE_STRING:response = GetInstance()->ReverseStringHandler(requestArgs); break;
		case Action::SET_INTEGER:response = GetInstance()->SetIntegerHandler(requestArgs); break;
		case Action::SET_STRING:response = GetInstance()->SetStringHandler(requestArgs); break;
		case Action::GET_OBJECT:response = GetInstance()->GetObjHandler(requestArgs); break;
		case Action::ECHO: response = GetInstance()->EchoHandler(requestArgs); break;
		}
	}
	catch (StreamLabsException& e)
	{
		response = Response(e);
	}
	return response;
}

//TODO add map with log
Response StreamLabsServer::EchoHandler(json requestArgs)
{
	string data = requestArgs[DATA];
	string response = "Echo: " + data;
	return Response(StatusCode::MY_SUCCESS, response);
}

DummyClass* StreamLabsServer::GetObj(int id)
{
	map<int, DummyClass*>::iterator it = customObjects.find(id);
	if (it != customObjects.end())
	{
		return it->second;
	}
	else
	{
		throw StreamLabsException(StatusCode::ID_NOT_FOUND);
	}
}
Response StreamLabsServer::CreateDummyObjectHandler()
{
	DummyClass* dummy = new DummyClassServerImpl();
	customObjects[dummy->GetId()] = dummy;
	json responseArgs;
	responseArgs[OBJ_ID] = dummy->GetId();
	return Response(StatusCode::MY_SUCCESS, responseArgs.dump());
}
Response StreamLabsServer::DecrementIntegerHandler(json requestArgs)
{
	int id = requestArgs[OBJ_ID];
	DummyClass* obj = GetObj(id);
	obj->DecrementInteger();
	return Response(StatusCode::MY_SUCCESS, obj->ToString());
}
Response StreamLabsServer::GetIntegerHandler(json requestArgs)
{
	int id = requestArgs[OBJ_ID];
	DummyClass* obj = GetObj(id);
	json result;
	result[INTEGER_VALUE] = obj->GetInteger();
	return Response(StatusCode::MY_SUCCESS, result.dump());
}
Response StreamLabsServer::GetStringHandler(json requestArgs) {
	int id = requestArgs[OBJ_ID];
	DummyClass* obj = GetObj(id);
	json result;
	result[STRING_VALUE] = obj->GetString();
	return Response(StatusCode::MY_SUCCESS, result.dump());
}
Response StreamLabsServer::IncrementIntegerHandler(json requestArgs) {
	int id = requestArgs[OBJ_ID];
	DummyClass* obj = GetObj(id);
	obj->IncrementInteger();
	return Response(StatusCode::MY_SUCCESS, obj->ToString());
}
Response StreamLabsServer::ReverseStringHandler(json requestArgs) {
	int id = requestArgs[OBJ_ID];
	DummyClass* obj = GetObj(id);
	obj->ReverseString();
	return Response(StatusCode::MY_SUCCESS, obj->ToString());
}
Response StreamLabsServer::SetIntegerHandler(json requestArgs) {
	int id = requestArgs[OBJ_ID];
	int integer = requestArgs[INTEGER_VALUE];
	DummyClass* obj = GetObj(id);
	obj->SetInteger(integer);
	return  Response(StatusCode::MY_SUCCESS, obj->ToString());
}
Response StreamLabsServer::SetStringHandler(json requestArgs) {
	int id = requestArgs[OBJ_ID];
	string str = requestArgs[STRING_VALUE];
	DummyClass* obj = GetObj(id);
	obj->SetString(str);
	return Response(StatusCode::MY_SUCCESS, obj->ToString());
}
Response StreamLabsServer::GetObjHandler(json requestArgs) {
	int id = requestArgs[OBJ_ID];
	DummyClass* obj = GetObj(id);
	return Response(StatusCode::MY_SUCCESS, obj->ToString());
}

void StreamLabsServer::LogRequest(Request request)
{
	time_t timer;
	time(&timer);
	requestLog.insert(std::pair<time_t, Request>(timer, request));
	
	
}
int _tmain(VOID)
{
	StreamLabsServer::GetInstance()->StartServer();
	delete StreamLabsServer::GetInstance();
	return 0;
}