#include "StreamLabsClient.h"
StreamLabsClient* StreamLabsClient::instance;

StreamLabsClient::StreamLabsClient()
{
	lpszPipename = TEXT(PIPE_NAME);
}

StreamLabsClient::~StreamLabsClient()
{
	CloseHandle(hPipe);
}

int StreamLabsClient::ConnectPipe()
{
	// Try to open a named pipe; wait for it, if necessary. [Microsoft] 
	BOOL   fSuccess = FALSE;
	DWORD  dwMode;
	while (1)
	{
		hPipe = CreateFile(
			lpszPipename,   // pipe name [Microsoft]
			GENERIC_READ |  // read and write access [Microsoft] 
			GENERIC_WRITE,
			0,              // no sharing [Microsoft]
			NULL,           // default security attributes [Microsoft]
			OPEN_EXISTING,  // opens existing pipe [Microsoft]
			0,              // default attributes [Microsoft]
			NULL);          // no template file [Microsoft]

	  // Break if the pipe handle is valid. [Microsoft]

		if (hPipe != INVALID_HANDLE_VALUE)
			break;

		// Exit if an error other than ERROR_PIPE_BUSY occurs. [Microsoft] 

		if (GetLastError() != ERROR_PIPE_BUSY)
		{
			_tprintf(TEXT("Could not open pipe. GLE=%d\n"), GetLastError());
			return -1;
		}

		// All pipe instances are busy, so wait for 20 seconds. [Microsoft]

		if (!WaitNamedPipe(lpszPipename, 20000))
		{
			printf("Could not open pipe: 20 second wait timed out.");
			return -1;
		}
	}
	// The pipe connected; change to message-read mode. [Microsoft]

	dwMode = PIPE_READMODE_MESSAGE;
	fSuccess = SetNamedPipeHandleState(
		hPipe,    // pipe handle [Microsoft]
		&dwMode,  // new pipe mode [Microsoft]
		NULL,     // don't set maximum bytes [Microsoft]
		NULL);    // don't set maximum time [Microsoft]
	if (!fSuccess)
	{
		_tprintf(TEXT("SetNamedPipeHandleState failed. GLE=%d\n"), GetLastError());
		return -1;
	}

	return 0;
}

int StreamLabsClient::SendRequest(Request request)
{
	string lpvMessage = request.ToString();
	TCHAR  chBuf[BUFSIZE];
	BOOL   fSuccess = FALSE;
	DWORD  cbToWrite, cbWritten;

	// Send a message to the pipe server. [Microsoft]

	cbToWrite = (strlen(lpvMessage.c_str()) + 1) * sizeof(char);
	if (cbToWrite > BUFSIZE)
		throw StreamLabsException(StatusCode::MESSAGE_TOO_LONG);
	printf("Sending %d byte message: %s\n", cbToWrite, lpvMessage.c_str());

	fSuccess = WriteFile(
		hPipe,                  // pipe handle [Microsoft] 
		lpvMessage.c_str(),             // message [Microsoft]
		cbToWrite,              // message length [Microsoft]
		&cbWritten,             // bytes written [Microsoft]
		NULL);                  // not overlapped [Microsoft]

	if (!fSuccess)
	{
		_tprintf(TEXT("WriteFile to pipe failed. GLE=%d\n"), GetLastError());
		return -1;
	}
	return 0;
}


Response StreamLabsClient::ReceiveReply()
{
	char* chBuf = new char[BUFSIZE];
	BOOL   fSuccess = FALSE;
	DWORD  cbRead;

	// Read from the pipe. [Microsoft]
	fSuccess = ReadFile(
		hPipe,    // pipe handle [Microsoft]
		chBuf,    // buffer to receive reply [Microsoft] 
		BUFSIZE * sizeof(char),  // size of buffer [Microsoft]
		&cbRead,  // number of bytes read [Microsoft]
		NULL);    // not overlapped [Microsoft]

	if (!fSuccess && GetLastError() != ERROR_MORE_DATA)
		throw StreamLabsException(StatusCode::READ_FAIL);

	printf("*********Reply received: %s\n", chBuf);

	unique_ptr<Response> response(new Response(string(chBuf)));
	if (response->IsError())
		throw StreamLabsException(response->GetStatusCode());
	return *response;

}

string StreamLabsClient::SendSimpleData(string data)
{
	json requestArgs;
	requestArgs[DATA] = data;
	std::unique_ptr<Request> request(new Request(Action::ECHO, requestArgs));

	StreamLabsClient::GetInstance()->SendRequest(*request);
	Response response = StreamLabsClient::GetInstance()->ReceiveReply();
	if (response.IsError())
		throw StreamLabsException(response.GetStatusCode());
	return response.GetResponseData();
}

// This code could be later extended to create different types of objects
int StreamLabsClient::CreateObj(int objCode)
{
	return DummyClassClientImpl::CreateObj();
}

DummyClass* StreamLabsClient::GetObj(int id)
{
	return DummyClassClientImpl::GetObj(id);
}

