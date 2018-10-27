#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include "StreamLabsClient.h"
#include "Request.h"


int _tmain(int argc, TCHAR *argv[])
{
}
/*
	StreamLabsClient::GetInstance()->ConnectPipe();

	do
	{
		int primaryAction;
		cout << "Please select desired action (1: Create new object, 2: Execute function on particular instance, 3: Retrieve an instance" << endl;
		cin >> primaryAction;
		switch (primaryAction)
		{
		case 1: CreateObjectHandler(); break;
		case 2: CarryOutFunctionHandler(); break;
		case 3: GetObjectHandler(); break;
		}
	} while (cin.getline() != "exit");

	return 0;
	_getch();
	delete StreamLabsClient::GetInstance();

	return 0;
}

void CreateObjectHandler()
{
	int id = StreamLabsClient::GetInstance()->CreateObj();
	cout << "A new object has been created with the id: " << id << endl;
}
void CarryOutFunctionHandler()
{
	int id;
	int secondaryAction;
	enum Action { CREATE_DUMMY_OBJECT, INCREMENT_INTEGER, DECREMENT_INTEGER, GET_INTEGER, SET_INTEGER, REVERSE_STRING, GET_STRING, SET_STRING, GET_OBJECT };
	cout << "Please enter the id of the instace " << endl;
	//TODO add check that it is a valid id
	cin >> id;
	cout << "Please enter the desired function ("
		<< Action::GET_INTEGER << ": get integer, "
		<< Action::SET_INTEGER << ": set integer, "
		<< Action::INCREMENT_INTEGER << ": increment integer, "
		<< Action::DECREMENT_INTEGER << ": decrement integer, "
		<< Action::GET_STRING << ": get string, "
		<< Action::SET_STRING << ": set string, "
		<< Action::REVERSE_STRING << ": reverse string, "
		<< endl;
	cin >> secondaryAction;
	switch (secondaryAction)
	{
	case Action::GET_INTEGER: GetIntegerHandler(); break;
	case  Action::SET_INTEGER: SetIntegerHandler(); break;
	case Action::INCREMENT_INTEGER:IncrementIntegerHandler(); break;
	case Action::DECREMENT_INTEGER: DecrementIntegerHandler(); break;
	case  Action::GET_STRING: GetStringHandler(); break;
	case  Action::SET_STRING:SetStringHandler(); break;
			case Action::REVERSE_STRING << ": reverse string, "

	}
	
}
void GetObjectHandler()
{}
*/