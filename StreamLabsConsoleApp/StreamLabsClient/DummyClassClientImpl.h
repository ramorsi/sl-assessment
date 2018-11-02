#pragma once
#include "DummyClass.h"
#include "Request.h"
#include "StreamLabsClient.h"
class DummyClassClientImpl :public DummyClass
{
public:
	DummyClassClientImpl();
	DummyClassClientImpl(int id, int integer_value, string string_value);

	void IncrementInteger();
	void DecrementInteger();
	int GetInteger();
	void SetInteger(int newValue);

	void ReverseString();
	string GetString();
	void SetString(string newString);
	//string ToString();
	
	static int CreateObj();
	static DummyClass* GetObj(int id);
//	json GetObj();

};

