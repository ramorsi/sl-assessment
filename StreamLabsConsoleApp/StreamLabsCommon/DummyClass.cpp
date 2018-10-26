#include "DummyClass.h"

int DummyClass::counter = 0;

DummyClass::DummyClass()
{
	this->id = counter++;
}

//TODO add constructors using int, int and string, string
DummyClass::~DummyClass()
{
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
