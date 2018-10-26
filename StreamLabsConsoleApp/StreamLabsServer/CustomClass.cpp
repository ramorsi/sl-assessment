#include "CustomClass.h"
#include <nlohmann/json.hpp>

int CustomClass::counter = 0;

CustomClass::CustomClass()
{
	this->id = counter++;
}

CustomClass::~CustomClass()
{
}

void CustomClass::IncrementInteger()
{
	a++;
}

void CustomClass::DecrementInteger()
{
	a--;
}

int CustomClass::GetInteger()
{
	return a;
}

void CustomClass::SetInteger(int newValue)
{
	a = newValue;
}

void CustomClass::ReverseString()
{
}

string CustomClass::GetString()
{
	return str;
}

void CustomClass::SetString(string newString)
{
	str = newString;
}
