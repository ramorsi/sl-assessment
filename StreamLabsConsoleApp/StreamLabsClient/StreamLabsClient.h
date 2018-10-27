#pragma once
#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include "ServerAccess.h"

using namespace std;
#define BUFSIZE 512
class StreamLabsClient
{
	static StreamLabsClient* instance;
	StreamLabsClient();

private:
	HANDLE hPipe;
	LPCTSTR lpszPipename; //Assuming each client will connect to only one server
public:
	static StreamLabsClient* GetInstance() {
		if (!instance)
			instance = new StreamLabsClient;
		return instance;
	}
	int ConnectPipe();
	int SendRequest(string lpvMessage);
	int ReceiveReply();

	void IncrementInteger(int objId);
	void DecrementInteger(int objId);
	int GetInteger(int objId);
	void SetInteger(int objId, int newValue);

	void ReverseString(int objId);
	string GetString(int objId);
	void SetString(int objId, string newString);
	json GetObj(int id);
	int CreateObj();
		

	~StreamLabsClient();
};