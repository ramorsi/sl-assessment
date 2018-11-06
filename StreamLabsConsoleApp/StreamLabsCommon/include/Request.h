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

enum Action { CREATE_DUMMY_OBJECT, GET_INTEGER, SET_INTEGER, INCREMENT_INTEGER, DECREMENT_INTEGER, GET_STRING, SET_STRING, REVERSE_STRING, TO_STRING, GET_OBJECT, ECHO, RUN_FUNCTION };

class  __declspec(dllexport) Request {
	Action action_;
	json request_args_;

public:
	Request(Action action);
	Request(Action action, json requestArgs);
	Request(string jsonStr);

	~Request();
	int GetAction();
	json GetRequestArgs();
	string ToString();

};
