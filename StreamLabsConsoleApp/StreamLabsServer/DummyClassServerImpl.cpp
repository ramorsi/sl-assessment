#include "DummyClassServerImpl.h"
int DummyClassServerImpl::counter = 0;

DummyClassServerImpl::DummyClassServerImpl()
{
	this->id_ = counter++;
}

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

