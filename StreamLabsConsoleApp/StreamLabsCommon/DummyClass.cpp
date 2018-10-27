#include "DummyClass.h"
//TODO remove this implementation, move it to server side and change DummyClass to an interface!
int DummyClass::counter = 0;

DummyClass::DummyClass()
{
	this->id = counter++;
}

//TODO add constructors using int, int and string, string
DummyClass::~DummyClass()
{
}

int DummyClass::GetId()
{
	return id;
}

void DummyClass::IncrementInteger()
{
	a++;
}

void DummyClass::DecrementInteger()
{
	a--;
}

int DummyClass::GetInteger()
{
	return a;
}

void DummyClass::SetInteger(int newValue)
{
	a = newValue;
}

void DummyClass::ReverseString()
{
}

string DummyClass::GetString()
{
	return str;
}

void DummyClass::SetString(string newString)
{
	str = newString;
}

string DummyClass::ToString()
{
	json dummyJson;
	dummyJson[INTEGER] = this->a;
	dummyJson[STRING] = this->str;
	dummyJson[ID] = this->id;
	return string();
}
