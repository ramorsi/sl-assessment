#ifdef DUMMYCLASS_EXPORTS  
#define DUMMMYCLASS_API __declspec(dllexport)   
#else  
#define DUMMYCLASS_API __declspec(dllimport)   
#endif 
#pragma once
#include <string>
#include "Constants.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace std;

class  __declspec(dllexport) DummyClass
{
public:

	int integerValue = 0;
	int id;
	string stringValue;
	static int counter;

	virtual int GetId() { return id; }
	virtual void IncrementInteger() = 0;
	virtual void DecrementInteger() = 0;
	virtual int GetInteger() = 0;
	virtual void SetInteger(int newValue) = 0;

	virtual void ReverseString() = 0;
	virtual string GetString() = 0;
	virtual void SetString(string newString) = 0;
	virtual string ToString() {
		json dummyJson;
		dummyJson[INTEGER] = this->integerValue;
		dummyJson[STRING] = this->stringValue;
		dummyJson[OBJ_ID] = this->id;
		return dummyJson.dump();
	}
};

