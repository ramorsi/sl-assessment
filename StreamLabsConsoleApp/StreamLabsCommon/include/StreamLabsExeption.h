#pragma once

#include <iostream>
#include <exception>

#include "Constants.h"

using namespace std;
enum StatusCode { MY_SUCCESS, MY_ERROR, ID_NOT_FOUND, INVALID_RESPONSE_FORMAT, READ_FAIL, MESSAGE_TOO_LONG };

struct StreamLabsException : public exception
{
	StatusCode exception_id_;
	StreamLabsException(StatusCode exception_id) :exception_id_(exception_id)
	{

	}
	const char * what() const throw ()
	{
		switch (exception_id_)
		{
		case ID_NOT_FOUND: return "Id not found. No object was created with that id.";
		case INVALID_RESPONSE_FORMAT: return "Invalid response format. Unable to parse response.";
		case READ_FAIL:return "ReadFile from pipe failed.";
		case MESSAGE_TOO_LONG: return "Cannot send message. Message too long.";
		default: return "Unknown exception occured.";
		}
	}
};