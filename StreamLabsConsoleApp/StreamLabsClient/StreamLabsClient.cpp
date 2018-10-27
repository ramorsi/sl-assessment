#include "StreamLabsClient.h"
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

int StreamLabsClient::SendRequest(string lpvMessage)
{
	TCHAR  chBuf[BUFSIZE];
	BOOL   fSuccess = FALSE;
	DWORD  cbToWrite, cbWritten;

	// Send a message to the pipe server. 

	//cbToWrite = (lstrlen(lpvMessage) + 1) * sizeof(TCHAR);
	//TODO check what to do about strings and TCHARs
	cbToWrite = (strlen(lpvMessage.c_str()) + 1) * sizeof(char);
	_tprintf(TEXT("Sending %d byte message: \"%s\"\n"), cbToWrite, lpvMessage);

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
int StreamLabsClient::ReceiveReply()
{
	TCHAR  chBuf[BUFSIZE];
	BOOL   fSuccess = FALSE;
	DWORD  cbRead;

	do
	{
		// Read from the pipe. 

		fSuccess = ReadFile(
			hPipe,    // pipe handle 
			chBuf,    // buffer to receive reply 
			BUFSIZE * sizeof(TCHAR),  // size of buffer 
			&cbRead,  // number of bytes read 
			NULL);    // not overlapped 

		if (!fSuccess && GetLastError() != ERROR_MORE_DATA)
			break;

		_tprintf(TEXT("\"%s\"\n"), chBuf);
	} while (!fSuccess);  // repeat loop if ERROR_MORE_DATA 

	if (!fSuccess)
	{
		_tprintf(TEXT("ReadFile from pipe failed. GLE=%d\n"), GetLastError());
		return -1;
	}

	printf("\n<End of message, press ENTER to terminate connection and exit>");
	return 0;
}


void StreamLabsClient::IncrementInteger(int objId)
{
	json requestArgs;
	requestArgs[OBJ_ID] = objId;
	Request* request = new Request(Action::INCREMENT_INTEGER, requestArgs);
	SendRequest(request->ToString());
	//TODO refactor this, reply should be accessible here
	ReceiveReply();
	delete request;
}

void StreamLabsClient::DecrementInteger(int objId)
{
	json requestArgs;
	requestArgs[OBJ_ID] = objId;
	Request* request = new Request(Action::DECREMENT_INTEGER, requestArgs);
	SendRequest(request->ToString());
	//TODO refactor this, reply should be accessible here
	ReceiveReply();
	delete request;

}

int StreamLabsClient::GetInteger(int objId)
{
	json requestArgs;
	requestArgs[OBJ_ID] = objId;
	Request* request = new Request(Action::GET_INTEGER, requestArgs);
	SendRequest(request->ToString());
	//TODO refactor this, reply should be accessible here
	ReceiveReply();
	delete request;
	return 0; //FIX THIS, should be actual value returned!
}

void StreamLabsClient::SetInteger(int objId, int newValue)
{
	json requestArgs;
	requestArgs[OBJ_ID] = objId;
	requestArgs[INTEGER] = newValue;
	Request* request = new Request(Action::SET_INTEGER, requestArgs);
	SendRequest(request->ToString());
	//TODO refactor this, reply should be accessible here
	ReceiveReply();
	delete request;
}

void StreamLabsClient::ReverseString(int objId)
{
	json requestArgs;
	requestArgs[OBJ_ID] = objId;
	Request* request = new Request(Action::REVERSE_STRING, requestArgs);
	SendRequest(request->ToString());
	//TODO refactor this, reply should be accessible here
	ReceiveReply();
	delete request;
}

string StreamLabsClient::GetString(int objId)
{
	json requestArgs;
	requestArgs[OBJ_ID] = objId;
	Request* request = new Request(Action::GET_STRING, requestArgs);
	SendRequest(request->ToString());
	//TODO refactor this, reply should be accessible here
	ReceiveReply();
	delete request;
	return ""; //TODO change this to actual value
}

void StreamLabsClient::SetString(int objId, string newString)
{
	json requestArgs;
	requestArgs[OBJ_ID] = objId;
	requestArgs[STRING] = newString;
	Request* request = new Request(Action::SET_STRING, requestArgs);
	SendRequest(request->ToString());
	//TODO refactor this, reply should be accessible here
	ReceiveReply();
	delete request;
}

json StreamLabsClient::GetObj(int objId)
{
	json requestArgs;
	requestArgs[OBJ_ID] = objId;
	Request* request = new Request(Action::GET_OBJECT, requestArgs);
	SendRequest(request->ToString());
	//TODO refactor this, reply should be accessible here
	ReceiveReply();
	delete request;
	return json(); //TODO change this to actual value
}

int StreamLabsClient::CreateObj()
{
	json requestArgs;
	Request* request = new Request(Action::CREATE_DUMMY_OBJECT, requestArgs);
	SendRequest(request->ToString());
	//TODO refactor this, reply should be accessible here
	ReceiveReply();
	delete request;
	return 0; //TODO change this to actual value

}
