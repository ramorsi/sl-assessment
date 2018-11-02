//Dummy interface implemented by both the client and server
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

	int integer_value_ = 0;
	int id_;
	string string_value_;
	static int counter;
	DummyClass() {}
	DummyClass(int id, int integer_value, string string_value) :id_(id),integer_value_(integer_value), string_value_(string_value){};
	virtual ~DummyClass() {}
	virtual int GetId() { return id_; }
	virtual void IncrementInteger() = 0;
	virtual void DecrementInteger() = 0;
	virtual int GetInteger() = 0;
	virtual void SetInteger(int newValue) = 0;

	virtual void ReverseString() = 0;
	virtual string GetString() = 0;
	virtual void SetString(string newString) = 0;
	virtual string ToString() {
		json dummyJson;
		dummyJson[INTEGER_VALUE] = this->integer_value_;
		dummyJson[STRING_VALUE] = this->string_value_;
		dummyJson[OBJ_ID] = this->id_;
		return dummyJson.dump();
	}
};

