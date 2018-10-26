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
private:
	HANDLE hPipe;
	LPCTSTR lpszPipename; //Assuming each client will connect to only one server
public:
	StreamLabsClient();
	int ConnectPipe();
	int SendRequest(string lpvMessage);
	int ReceiveReply();

	void IncrementInteger(int objId);
	/*	void DecrementInteger();
		int GetInteger();
		void SetInteger(int newValue);

		void ReverseString();
		string GetString();
		void SetString(string newString);
		GetObj(int id);
		*/

	~StreamLabsClient();
};