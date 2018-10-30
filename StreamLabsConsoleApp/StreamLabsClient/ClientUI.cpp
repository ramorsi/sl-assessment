#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include "StreamLabsClient.h"
#include "Request.h"

void SendSimpleDataHandler()
{
	cout << "Please enter the text you would like to send" << endl;
	string input;
	cin >> input;
	string result = StreamLabsClient::GetInstance()->SendSimpleData(input);
	cout << result << endl;
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
		/*
	case Action::GET_INTEGER: GetIntegerHandler(); break;
	case  Action::SET_INTEGER: SetIntegerHandler(); break;
	case Action::INCREMENT_INTEGER:IncrementIntegerHandler(); break;
	case Action::DECREMENT_INTEGER: DecrementIntegerHandler(); break;
	case  Action::GET_STRING: GetStringHandler(); break;
	case  Action::SET_STRING:SetStringHandler(); break;
			case Action::REVERSE_STRING << ": reverse string, "
			*/
	}

}
void GetObjectHandler()
{
	cout << "Please enter the id of the object you would like to retrieve" << endl;
	int id;
	cin >> id;
	DummyClass* dummy = StreamLabsClient::GetInstance()->GetObj(id);
	cout << dummy->ToString() << endl;
	//TODO make printing pretty
}

int _tmain(int argc, TCHAR *argv[])
{
	StreamLabsClient::GetInstance()->ConnectPipe();

	while(true)
	{
		string primaryActionStr;
		//TODO refactor this and set as enums
		cout << "Please select an action (1: Send simple data, 2: Create a new object, 3: Execute function on particular instance, 4: Retrieve an instance)" << endl;
		cin >> primaryActionStr;
		if (primaryActionStr == "q")
			break;
		int primaryAction = atoi(primaryActionStr.c_str());
		switch (primaryAction)
		{
		case 1: SendSimpleDataHandler(); break; //TODO Echo function
		case 2: CreateObjectHandler(); break;
		case 3: CarryOutFunctionHandler(); break;
		case 4: GetObjectHandler(); break;
		}
	} 
	_getch();
	delete StreamLabsClient::GetInstance();

	return 0;
}

