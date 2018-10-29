#pragma once
#include "DummyClass.h"
#include "Request.h"
#include "StreamLabsClient.h"
class DummyClassClientImpl :public DummyClass
{
public:
	DummyClassClientImpl();
	~DummyClassClientImpl();

	int GetId() = 0; //Create obj
	void IncrementInteger();
	void DecrementInteger();
	int GetInteger();
	void SetInteger(int newValue);

	void ReverseString();
	string GetString();
	void SetString(string newString);
	string ToString() = 0;
	
	static int CreateObj();

//	json GetObj();

};

