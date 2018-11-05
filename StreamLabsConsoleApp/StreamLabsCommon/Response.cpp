#include "Response.h"

Response::Response(StatusCode statusCode)
{
	this->status_code_ = statusCode;
}

Response::Response(StatusCode statusCode, string responseStr)
{
	this->status_code_ = statusCode;
	this->response_str = responseStr;
}
Response::Response(StreamLabsException e)
{
	this->status_code_ = e.exception_id_;
	this->response_str = e.what();
}

Response::Response(string jsonStr)
{
	try {
		json responseJson = json::parse(jsonStr);
		this->status_code_ = responseJson[STATUS_CODE];
		this->response_str = responseJson[RESPONSE];

	}
	catch (...)
	{
		throw StreamLabsException(StatusCode::INVALID_RESPONSE_FORMAT);
	}
}

Response::~Response()
{
}

string Response::GetResponseData()
{
	return response_str;
}

StatusCode Response::GetStatusCode()
{
	return this->status_code_;
}

bool Response::IsError()
{
	return this->status_code_ != StatusCode::MY_SUCCESS;
}

string Response::ToString()
{
	json responseJson;
	responseJson[STATUS_CODE] = this->status_code_;
	responseJson[RESPONSE] = this->response_str;
	return responseJson.dump();
}
