#include "DummyClassClientImpl.h"



DummyClassClientImpl::DummyClassClientImpl()
{
	json requestArgs;
	Request* request = new Request(Action::CREATE_DUMMY_OBJECT, requestArgs);
	StreamLabsClient::GetInstance()->SendRequest(request);
	//TODO refactor this, reply should be accessible here
	StreamLabsClient::GetInstance()->ReceiveReply();
	delete request;
	id = 0; //TODO change this to actual value
}
//TODO change this to be c++ syntax
DummyClassClientImpl::DummyClassClientImpl(int id, int a, string str)
{
	this->id = id;
	this->integerValue = a;
	this->stringValue = str;
}


DummyClassClientImpl::~DummyClassClientImpl()
{
}

void DummyClassClientImpl::IncrementInteger()
{
	json requestArgs;
	requestArgs[OBJ_ID] = id;
	Request* request = new Request(Action::INCREMENT_INTEGER, requestArgs);
	StreamLabsClient::GetInstance()->SendRequest(request);
	//TODO refactor this, reply should be accessible here
	Response* response = StreamLabsClient::GetInstance()->ReceiveReply();
	json responseJson = json::parse(response->GetResponseData());
	this->integerValue = responseJson[INTEGER];
	delete request;
	delete response;
}

void DummyClassClientImpl::DecrementInteger()
{
	json requestArgs;
	requestArgs[OBJ_ID] = id;
	Request* request = new Request(Action::DECREMENT_INTEGER, requestArgs);
	StreamLabsClient::GetInstance()->SendRequest(request);
	//TODO refactor this, reply should be accessible here
	Response* response = StreamLabsClient::GetInstance()->ReceiveReply();
	json responseJson = json::parse(response->GetResponseData());
	this->integerValue = responseJson[INTEGER];
	delete request;
	delete response;
}

int DummyClassClientImpl::GetInteger()
{
	json requestArgs;
	requestArgs[OBJ_ID] = id;
	Request* request = new Request(Action::GET_INTEGER, requestArgs);
	StreamLabsClient::GetInstance()->SendRequest(request);
	Response* response = StreamLabsClient::GetInstance()->ReceiveReply();
	json responseJson = json::parse(response->GetResponseData());
	this->integerValue = responseJson[INTEGER];

	delete request;
	delete response;
	return this->integerValue; //FIX THIS, should be actual value returned!
}

void DummyClassClientImpl::SetInteger( int newValue)
{
	json requestArgs;
	requestArgs[OBJ_ID] = id;
	requestArgs[INTEGER] = newValue;
	Request* request = new Request(Action::SET_INTEGER, requestArgs);
	StreamLabsClient::GetInstance()->SendRequest(request);
	Response* response = StreamLabsClient::GetInstance()->ReceiveReply();
	json responseJson = json::parse(response->GetResponseData());
	this->integerValue = responseJson[INTEGER];

	delete request;
}

void DummyClassClientImpl::ReverseString()
{
	json requestArgs;
	requestArgs[OBJ_ID] = id;
	Request* request = new Request(Action::REVERSE_STRING, requestArgs);
	StreamLabsClient::GetInstance()->SendRequest(request);
	Response* response = StreamLabsClient::GetInstance()->ReceiveReply();
	json responseJson = json::parse(response->GetResponseData());
	this->stringValue = responseJson[STRING];

	delete request;
	delete response;
}

string DummyClassClientImpl::GetString()
{
	json requestArgs;
	requestArgs[OBJ_ID] = id;
	Request* request = new Request(Action::GET_STRING, requestArgs);
	StreamLabsClient::GetInstance()->SendRequest(request);
	//TODO refactor this, reply should be accessible here
	Response* response = StreamLabsClient::GetInstance()->ReceiveReply();
	json responseJson = json::parse(response->GetResponseData());
	this->stringValue = responseJson[STRING];

	delete request;
	delete response;
	return this->stringValue;
}

void DummyClassClientImpl::SetString(string newString)
{
	json requestArgs;
	requestArgs[OBJ_ID] = id;
	requestArgs[STRING] = newString;
	Request* request = new Request(Action::SET_STRING, requestArgs);
	StreamLabsClient::GetInstance()->SendRequest(request);
	Response* response = StreamLabsClient::GetInstance()->ReceiveReply();
	json responseJson = json::parse(response->GetResponseData());
	this->stringValue = responseJson[STRING];
	delete response;
	delete request;
}

int DummyClassClientImpl::CreateObj()
{
	json requestArgs;
	Request* request = new Request(Action::CREATE_DUMMY_OBJECT);
	StreamLabsClient::GetInstance()->SendRequest(request);
	//TODO refactor this, reply should be accessible here
	Response* response = StreamLabsClient::GetInstance()->ReceiveReply();
	json responseData = json::parse(response->GetResponseData());
	int id = responseData[OBJ_ID];
	delete request;
	return id;
}



DummyClass* DummyClassClientImpl::GetObj(int id)
{
	json requestArgs;
	requestArgs[OBJ_ID] = id;
	Request* request = new Request(Action::GET_OBJECT, requestArgs);
	StreamLabsClient::GetInstance()->SendRequest(request);
	//TODO refactor this, reply should be accessible here
	Response* response = StreamLabsClient::GetInstance()->ReceiveReply();
	json responseData = json::parse(response->GetResponseData());
	int objId = responseData[OBJ_ID];
	int a = responseData[INTEGER];
	string str = responseData[STRING];
	DummyClass* dummy = new DummyClassClientImpl(objId, a , str);
	delete request;
	delete response;
	return dummy; 
}

//TODO assumption just one type of objects
