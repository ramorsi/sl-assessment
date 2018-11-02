#include "Request.h"

//TODO convention for instance vars
Request::Request(Action action, json requestArgs)
{
	this->action_ = action;
	this->request_args_ = requestArgs;
}
Request::Request(Action action)
{
	this->action_ = action;
}
Request::Request(string jsonStr)
{
	json responseJson = json::parse(jsonStr);
	this->action_ = responseJson[ACTION];
	this->request_args_ = responseJson[REQUEST_ARGS];
}

Request::~Request() {}
int Request::GetAction()
{
	return action_;
}
json Request::GetRequestArgs()
{
	return request_args_;
}
string Request::ToString()
{
	json requestStr;
	requestStr[ACTION] = this->action_;
	requestStr[REQUEST_ARGS] = this->request_args_;

	return requestStr.dump();
}