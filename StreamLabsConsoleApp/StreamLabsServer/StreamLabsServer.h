#include <windows.h> 
#include <stdio.h> 
#include <tchar.h>
#include <strsafe.h>
#include <string>
#include <map>
#include <iostream>

#include "DummyClass.h"
#include "nlohmann/json.hpp"
#include "Constants.h"
#include "Request.h"
#include "Response.h"
#include "DummyClassServerImpl.h"

//TODO check automatic variable
using json = nlohmann::json;
using namespace std;

class StreamLabsServer {
	static StreamLabsServer* instance;
	StreamLabsServer();
	~StreamLabsServer();
private:
	map<int, DummyClass*> customObjects;
public:
	static StreamLabsServer* GetInstance() {
		if (!instance)
			instance = new StreamLabsServer;
		return instance;
	}
	int StartServer();
	DummyClass* GetObj(int id);
	Response* CreateDummyObjectHandler();
	Response* DecrementIntegerHandler(json requestArgs);
	Response* GetIntegerHandler(json requestArgs);
	Response* GetStringHandler(json requestArgs);
	Response* IncrementIntegerHandler(json requestArgs); 
	Response* ReverseStringHandler(json requestArgs); 
	Response* SetIntegerHandler(json requestArgs); 
	Response* SetStringHandler(json requestArgs); 
	Response* GetObjHandler(json requestArgs);
	Response* EchoHandler(json requestArgs);


	static DWORD WINAPI InstanceThread(LPVOID lpvParam);
	static VOID GetAnswerToRequest(char* pchRequest,
		char* pchReply,
		LPDWORD pchBytes);

};

