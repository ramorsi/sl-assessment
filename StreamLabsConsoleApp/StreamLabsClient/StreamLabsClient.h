#ifdef STREAMLABSCLIENT_EXPORTS  
#define STREAMLABSCLIENT_API __declspec(dllexport)   
#else  
#define STREAMLABSCLIENT_API __declspec(dllimport)   
#endif 
#pragma once
#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <string>

#include "nlohmann/json.hpp"
#include "Request.h"
#include "Response.h"
#include "DummyClassClientImpl.h"
using json = nlohmann::json;
using namespace std;
#define BUFSIZE 512
class __declspec(dllexport) StreamLabsClient
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
	int SendRequest(Request request);
	Response ReceiveReply();

	string SendSimpleData(string data);
	//TODO change this to use class name and then map to object
	int CreateObj(int objCode=0);
	DummyClass* GetObj(int id);

	~StreamLabsClient();
};