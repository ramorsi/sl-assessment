//Main client class. Responsible for all i/o.
#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <limits>
#include "StreamLabsClient.h"
#include "Request.h"

void SendSimpleDataHandler()
{
	cout << "Please enter the text you would like to send" << endl;
	string input;
	cin.clear(); 
	cin.ignore(INT_MAX, '\n');

	getline(cin, input);
	string result = StreamLabsClient::GetInstance()->SendSimpleData(input);
	cout << result << endl;
}
void CreateObjectHandler()
{
	int id = StreamLabsClient::GetInstance()->CreateObj();
	cout << "A new object has been created with the id: " << id << endl;
}
void GetIntegerHandler(DummyClass* dummy)
{
	int integer = dummy->GetInteger();
	cout << "The current value of integer is: " << integer << endl;
}
void SetIntegerHandler(DummyClass* dummy)
{
	cout << "Please enter the integer value you want to set" << endl;
	int input;
	cin >> input;
	while (cin.fail())
	{
		cout << "Please enter a valid integer" << endl;
		cin.clear(); 
		cin.ignore(INT_MAX, '\n');

		cin >> input;
	}
	dummy->SetInteger(input);
	cout << "Integer currently set to: " << dummy->integer_value_ << endl;

}
void IncrementIntegerHandler(DummyClass* dummy)
{
	dummy->IncrementInteger();
	cout << "Integer incremented to: " << dummy->integer_value_ << endl;
}

void DecrementIntegerHandler(DummyClass* dummy)
{
	dummy->DecrementInteger();
	cout << "Integer decremented to: " << dummy->integer_value_ << endl;
}
void GetStringHandler(DummyClass* dummy)
{
	string str = dummy->GetString();
	cout << "Current string value is: " << dummy->string_value_ << endl;
}
void SetStringHandler(DummyClass* dummy)
{
	cout << "Enter new string" << endl;
	string input;
	cin >> input;
	dummy->SetString(input);
	cout << "String updated to: " << dummy->string_value_ << endl;
}
void ReverseStringHandler(DummyClass* dummy)
{
	dummy->ReverseString();
	cout << "String updated to: " << dummy->string_value_ << endl;
}
void GetObjectHandler()
{
	cout << "Please enter the id of the object you would like to retrieve" << endl;
	int id;
	cin >> id;
	DummyClass* dummy = StreamLabsClient::GetInstance()->GetObj(id);
	cout << dummy->ToString() << endl;
}
void CarryOutFunctionHandler()
{
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	int id;
	int secondaryAction;
	cout << "Please enter the id of the instance " << endl;
	//TODO add check that it is a valid id
	cin >> id;

	try {
		DummyClass* dummy = StreamLabsClient::GetInstance()->GetObj(id);
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

		case Action::GET_INTEGER: GetIntegerHandler(dummy); break;
		case  Action::SET_INTEGER: SetIntegerHandler(dummy); break;
		case Action::INCREMENT_INTEGER:IncrementIntegerHandler(dummy); break;
		case Action::DECREMENT_INTEGER: DecrementIntegerHandler(dummy); break;
		case  Action::GET_STRING: GetStringHandler(dummy); break;
		case  Action::SET_STRING:SetStringHandler(dummy); break;
		case Action::REVERSE_STRING:ReverseStringHandler(dummy); break;

		}

	}
	catch (StreamLabsException &e)
	{
		cout << e.what() << endl;
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}

int _tmain(int argc, TCHAR *argv[])
{
	StreamLabsClient::GetInstance()->ConnectPipe();

	while (true)
	{
		int primaryAction;
		cout << "Please select an action (1: Send simple data, 2: Create a new object, 3: Execute function on particular instance, 4: Retrieve an instance)" << endl;
		cin >> primaryAction;
		try {
			switch (primaryAction)
			{
			case 1: SendSimpleDataHandler(); break; 
			case 2: CreateObjectHandler(); break;
			case 3: CarryOutFunctionHandler(); break;
			case 4: GetObjectHandler(); break;
			default:cout << "You have an entered an invalid action" << endl;
			}
		}
		catch (StreamLabsException &e)
		{
			cout << e.what() << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');

		}
		catch (exception &ex)
		{
			cout << ex.what() << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');

		}

	}
	_getch();
	delete StreamLabsClient::GetInstance();

	return 0;
}

