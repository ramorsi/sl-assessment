#include "DummyClassServerImpl.h"
//TODO remove this implementation, move it to server side and change DummyClassServerImpl to an interface!
int DummyClassServerImpl::counter = 0;

DummyClassServerImpl::DummyClassServerImpl()
{
	this->id_ = counter++;
}

//TODO add constructors using int, int and string, string
DummyClassServerImpl::~DummyClassServerImpl()
{
}

int DummyClassServerImpl::GetId()
{
	return id_;
}

void DummyClassServerImpl::IncrementInteger()
{
	integer_value_++;
}

void DummyClassServerImpl::DecrementInteger()
{
	integer_value_--;
}

int DummyClassServerImpl::GetInteger()
{
	return integer_value_;
}

void DummyClassServerImpl::SetInteger(int newValue)
{
	integer_value_ = newValue;
}

void DummyClassServerImpl::ReverseString()
{
	reverse(string_value_.begin(), string_value_.end());
}

string DummyClassServerImpl::GetString()
{
	return string_value_;
}

void DummyClassServerImpl::SetString(string newString)
{
	string_value_ = newString;
}

