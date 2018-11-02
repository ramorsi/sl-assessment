#pragma once

#include <iostream>
#include <exception>

using namespace std;
enum StatusCode { MY_SUCCESS, MY_ERROR, ID_NOT_FOUND };

struct StreamLabsException : public exception
{
	int exception_id_;
	StreamLabsException(int exception_id):exception_id_(exception_id)
	{

	}
	const char * what() const throw ()
	{
		return "C++ Exception";
	}
};