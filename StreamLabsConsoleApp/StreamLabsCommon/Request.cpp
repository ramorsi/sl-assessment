#include "Request.h"

//TODO convention for instance vars
Request::Request(Action action, json requestArgs)
{
	this->action = action;
	this->requestArgs = requestArgs;
}
Request::Request(Action action)
{
	this->action = action;
}
Request::~Request() {}
string Request::ToString()
{
	json requestStr;
	requestStr[ACTION] = this->action;
	requestStr[REQUEST_ARGS] = this->requestArgs;

	return requestStr.dump();
}