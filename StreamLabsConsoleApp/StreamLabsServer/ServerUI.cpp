#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <string>

#include "StreamLabsServer.h"


using namespace std;

int _tmain(VOID)
{
	StreamLabsServer* server = StreamLabsServer::GetInstance();
	server->StartServer();
	return 0;
}