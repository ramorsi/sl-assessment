#ifdef REQUEST_EXPORTS  
#define REQUEST_API __declspec(dllexport)   
#else  
#define REQUEST_API __declspec(dllimport)   
#endif 
#pragma once

#include "nlohmann/json.hpp"
#include "Constants.h"
using namespace std;
using json = nlohmann::json;

enum Action {CREATE_DUMMY_OBJECT,INCREMENT_INTEGER, DECREMENT_INTEGER, GET_INTEGER, SET_INTEGER, REVERSE_STRING, GET_STRING, SET_STRING, GET_OBJECT, ECHO};

class  __declspec(dllexport) Request {
	Action action;
	json requestArgs;

public:
	Request(Action action);
	Request(Action action, json requestArgs);
	~Request();
	string ToString();

};
