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
	integerValue++;
}

void DummyClassServerImpl::DecrementInteger()
{
	integerValue--;
}

int DummyClassServerImpl::GetInteger()
{
	return integerValue;
}

void DummyClassServerImpl::SetInteger(int newValue)
{
	integerValue = newValue;
}

void DummyClassServerImpl::ReverseString()
{
	reverse(stringValue.begin(), stringValue.end());
}

string DummyClassServerImpl::GetString()
{
	return stringValue;
}

void DummyClassServerImpl::SetString(string newString)
{
	stringValue = newString;
}

