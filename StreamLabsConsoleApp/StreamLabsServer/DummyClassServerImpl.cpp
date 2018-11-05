//Main logic and implementation of the custom class to be invoked by the client
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

string DummyClassServerImpl::ToString() {
	json dummyJson;
	dummyJson[INTEGER_VALUE] = this->integer_value_;
	dummyJson[STRING_VALUE] = this->string_value_;
	dummyJson[OBJ_ID] = this->id_;
	return dummyJson.dump();
}


