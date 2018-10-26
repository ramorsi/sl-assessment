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
private:
	int a;
	int id;
	string str;
	static int counter;
public:
	DummyClass();
	~DummyClass();
	void IncrementInteger();
	void DecrementInteger();
	int GetInteger();
	void SetInteger(int newValue);

	void ReverseString();
	string GetString();
	void SetString(string newString);
	string ToString();

};

