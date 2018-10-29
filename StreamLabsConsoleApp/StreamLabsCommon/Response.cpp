#include "Response.h"

Response::Response(StatusCode statusCode)
{
	this->statusCode = statusCode;
}

Response::Response(StatusCode statusCode, string responseStr)
{
	this->statusCode = statusCode;
	this->responseStr = responseStr;
}
//TODO Exception handling
Response::Response(string jsonStr)
{
	json responseJson = json::parse(jsonStr);
	this->statusCode = responseJson[STATUS_CODE];
	this->responseStr = responseJson[RESPONSE];
}

Response::~Response()
{
}

string Response::GetResponseData()
{
	return responseStr;
}

string Response::ToString()
{
	json responseJson;
	responseJson[STATUS_CODE] = this->statusCode;
	responseJson[RESPONSE] = this->responseStr;
	return responseJson.dump();
}
