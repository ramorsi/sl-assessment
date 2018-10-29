
#ifdef RESPONSE_EXPORTS  
#define RESPONSE_API __declspec(dllexport)   
#else  
#define RESPONSE_API __declspec(dllimport)   
#endif 
#pragma once

#include "nlohmann/json.hpp"
#include "Constants.h"
using namespace std;
using json = nlohmann::json;

enum StatusCode {MY_SUCCESS, MY_ERROR};

class  __declspec(dllexport) Response
{
private:
	StatusCode statusCode;
	string responseStr;

public:
	Response(StatusCode statusCode);
	Response(StatusCode statusCode, string responseStr);
	Response(string json);
	~Response();
	string GetResponseData();
	string ToString();
};