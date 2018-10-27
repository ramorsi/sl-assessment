#include "DummyClassServerImpl.h"
//TODO remove this implementation, move it to server side and change DummyClassServerImpl to an interface!
int DummyClassServerImpl::counter = 0;

DummyClassServerImpl::DummyClassServerImpl()
{
	this->id = counter++;
}

//TODO add constructors using int, int and string, string
DummyClassServerImpl::~DummyClassServerImpl()
{
}

int DummyClassServerImpl::GetId()
{
	return id;
}

void DummyClassServerImpl::IncrementInteger()
{
	a++;
}

void DummyClassServerImpl::DecrementInteger()
{
	a--;
}

int DummyClassServerImpl::GetInteger()
{
	return a;
}

void DummyClassServerImpl::SetInteger(int newValue)
{
	a = newValue;
}

void DummyClassServerImpl::ReverseString()
{
}

string DummyClassServerImpl::GetString()
{
	return str;
}

void DummyClassServerImpl::SetString(string newString)
{
	str = newString;
}

string DummyClassServerImpl::ToString()
{
	json dummyJson;
	dummyJson[INTEGER] = this->a;
	dummyJson[STRING] = this->str;
	dummyJson[ID] = this->id;
	return string();
}
