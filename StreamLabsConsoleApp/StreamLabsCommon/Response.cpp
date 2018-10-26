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

Response::~Response()
{
}

string Response::ToString()
{
	json responseJson;
	responseJson[STATUS_CODE] = this->statusCode;
	responseJson[RESPONSE] = this->responseStr;
	return responseJson.dump();
}
