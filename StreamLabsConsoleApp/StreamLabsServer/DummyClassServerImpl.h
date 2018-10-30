#pragma once
#include "DummyClass.h"
class DummyClassServerImpl : public DummyClass
{
public:
	DummyClassServerImpl();
	//TODO add constructors using int, int and string, string
	~DummyClassServerImpl();

	int GetId();
	void IncrementInteger();
	void DecrementInteger();
	int GetInteger();
	void SetInteger(int newValue);

	void ReverseString();
	string GetString();
	void SetString(string newString);
	//string ToString();
	//json GetObj();

};