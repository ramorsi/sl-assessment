#include <windows.h> 
#include <stdio.h> 
#include <tchar.h>
#include <strsafe.h>
#include <string>
#include <map>

#include "CustomClass.h"

using namespace std;

class StreamLabsServer {
	static StreamLabsServer* instance;
	StreamLabsServer();
	//~StreamLabsServer();
private:
	map<int, CustomClass*> customObjects;
public:
	static StreamLabsServer* GetInstance() {
		if (!instance)
			instance = new StreamLabsServer;
		return instance;
	}
	int initServer();
	static DWORD WINAPI InstanceThread(LPVOID lpvParam);
	static VOID GetAnswerToRequest(LPTSTR pchRequest,
		LPTSTR pchReply,
		LPDWORD pchBytes);

};

