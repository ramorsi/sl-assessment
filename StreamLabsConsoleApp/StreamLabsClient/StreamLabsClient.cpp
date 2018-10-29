#include "StreamLabsClient.h"
StreamLabsClient* StreamLabsClient::instance;

StreamLabsClient::StreamLabsClient()
{
	//TODO change this
	lpszPipename = TEXT("\\\\.\\pipe\\streamlabs_pipe_name");


}

StreamLabsClient::~StreamLabsClient()
{
	CloseHandle(hPipe);
}

int StreamLabsClient::ConnectPipe()
{
	// Try to open a named pipe; wait for it, if necessary. 
	BOOL   fSuccess = FALSE;
	DWORD  dwMode;
	while (1)
	{
		hPipe = CreateFile(
			lpszPipename,   // pipe name 
			GENERIC_READ |  // read and write access 
			GENERIC_WRITE,
			0,              // no sharing 
			NULL,           // default security attributes
			OPEN_EXISTING,  // opens existing pipe 
			0,              // default attributes 
			NULL);          // no template file 

	  // Break if the pipe handle is valid. 

		if (hPipe != INVALID_HANDLE_VALUE)
			break;

		// Exit if an error other than ERROR_PIPE_BUSY occurs. 

		if (GetLastError() != ERROR_PIPE_BUSY)
		{
			_tprintf(TEXT("Could not open pipe. GLE=%d\n"), GetLastError());
			return -1;
		}

		// All pipe instances are busy, so wait for 20 seconds. 

		if (!WaitNamedPipe(lpszPipename, 20000))
		{
			printf("Could not open pipe: 20 second wait timed out.");
			return -1;
		}
	}
	// The pipe connected; change to message-read mode. 

	dwMode = PIPE_READMODE_MESSAGE;
	fSuccess = SetNamedPipeHandleState(
		hPipe,    // pipe handle 
		&dwMode,  // new pipe mode 
		NULL,     // don't set maximum bytes 
		NULL);    // don't set maximum time 
	if (!fSuccess)
	{
		_tprintf(TEXT("SetNamedPipeHandleState failed. GLE=%d\n"), GetLastError());
		return -1;
	}

	return 0;
}




//Change this to take request instead
int StreamLabsClient::SendRequest(Request* request)
{
	string lpvMessage = request->ToString();
	TCHAR  chBuf[BUFSIZE];
	BOOL   fSuccess = FALSE;
	DWORD  cbToWrite, cbWritten;

	// Send a message to the pipe server. 

	//cbToWrite = (lstrlen(lpvMessage) + 1) * sizeof(TCHAR);
	//TODO check what to do about strings and TCHARs
	cbToWrite = (strlen(lpvMessage.c_str()) + 1) * sizeof(char);
	//_tprintf(TEXT("Sending %d byte message: \"%s\"\n"), cbToWrite, lpvMessage);
	printf("Sending %d byte message: %s\n", cbToWrite, lpvMessage.c_str());

	fSuccess = WriteFile(
		hPipe,                  // pipe handle 
		lpvMessage.c_str(),             // message 
		cbToWrite,              // message length 
		&cbWritten,             // bytes written 
		NULL);                  // not overlapped 

	if (!fSuccess)
	{
		_tprintf(TEXT("WriteFile to pipe failed. GLE=%d\n"), GetLastError());
		return -1;
	}
	return 0;
}
//TODO updaate this tp return reply
Response* StreamLabsClient::ReceiveReply()
{
	char* chBuf = new char[BUFSIZE];
	BOOL   fSuccess = FALSE;
	DWORD  cbRead;

	do
	{
		// Read from the pipe. 

		fSuccess = ReadFile(
			hPipe,    // pipe handle 
			chBuf,    // buffer to receive reply 
			BUFSIZE * sizeof(char),  // size of buffer 
			&cbRead,  // number of bytes read 
			NULL);    // not overlapped 

		if (!fSuccess && GetLastError() != ERROR_MORE_DATA)
			break;

		//_tprintf(TEXT("\"%s\"\n"), chBuf);
		printf("%s\n", chBuf);
	} while (!fSuccess);  // repeat loop if ERROR_MORE_DATA 

	if (!fSuccess)
	{
		_tprintf(TEXT("ReadFile from pipe failed. GLE=%d\n"), GetLastError());
		return NULL;
	}
	//TODO fix this, what if size bigger than 512
	return new Response(string(chBuf));

	
}

string StreamLabsClient::SendSimpleData(string data)
{
	json requestArgs;
	requestArgs[DATA] = data;
	Request* request = new Request(Action::ECHO, requestArgs);
	StreamLabsClient::GetInstance()->SendRequest(request);
	//TODO refactor this, reply should be accessible here
	StreamLabsClient::GetInstance()->ReceiveReply();
	delete request;

	return string();
}

int StreamLabsClient::CreateObj(int objCode)
{
	//TODO this obj could be a dummy obj or any other registered objj type and should be dynamically selected
	return DummyClassClientImpl::CreateObj();
}



