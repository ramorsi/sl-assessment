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
	StreamLabsServer::GetInstance()->StartServer();
	delete StreamLabsServer::GetInstance(); 
	return 0;
}