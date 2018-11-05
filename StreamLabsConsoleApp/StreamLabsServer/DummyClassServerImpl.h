#pragma once
#include "DummyClass.h"
class DummyClassServerImpl : public DummyClass
{
public:
	DummyClassServerImpl();
	~DummyClassServerImpl();

	int GetId();
	void IncrementInteger();
	void DecrementInteger();
	int GetInteger();
	void SetInteger(int newValue);

	void ReverseString();
	string GetString();
	void SetString(string newString);
	string ToString();
	
};