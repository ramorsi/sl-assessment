
#ifdef RESPONSE_EXPORTS  
#define RESPONSE_API __declspec(dllexport)   
#else  
#define RESPONSE_API __declspec(dllimport)   
#endif 
#pragma once

#include "nlohmann/json.hpp"
#include "Constants.h"
#include "StreamLabsExeption.h"
using namespace std;
using json = nlohmann::json;

class  __declspec(dllexport) Response
{
private:
	StatusCode status_code_;
	string response_str;

public:
	Response(StatusCode statusCode);
	Response(StatusCode statusCode, string responseStr);
	Response(StreamLabsException e);
	Response(string json);
	~Response();
	string GetResponseData();
	StatusCode GetStatusCode();
	bool IsError();
	string ToString();
};