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
	StreamLabsClient::GetInstance()->ReceiveReply();
	delete request;
}

void DummyClassClientImpl::DecrementInteger()
{
	json requestArgs;
	requestArgs[OBJ_ID] = id;
	Request* request = new Request(Action::DECREMENT_INTEGER, requestArgs);
	StreamLabsClient::GetInstance()->SendRequest(request);
	//TODO refactor this, reply should be accessible here
	StreamLabsClient::GetInstance()->ReceiveReply();
	delete request;

}

int DummyClassClientImpl::GetInteger()
{
	json requestArgs;
	requestArgs[OBJ_ID] = id;
	Request* request = new Request(Action::GET_INTEGER, requestArgs);
	StreamLabsClient::GetInstance()->SendRequest(request);
	//TODO refactor this, reply should be accessible here
	StreamLabsClient::GetInstance()->ReceiveReply();
	delete request;
	return 0; //FIX THIS, should be actual value returned!
}

void DummyClassClientImpl::SetInteger( int newValue)
{
	json requestArgs;
	requestArgs[OBJ_ID] = id;
	requestArgs[INTEGER] = newValue;
	Request* request = new Request(Action::SET_INTEGER, requestArgs);
	StreamLabsClient::GetInstance()->SendRequest(request);
	//TODO refactor this, reply should be accessible here
	StreamLabsClient::GetInstance()->ReceiveReply();
	delete request;
}

void DummyClassClientImpl::ReverseString()
{
	json requestArgs;
	requestArgs[OBJ_ID] = id;
	Request* request = new Request(Action::REVERSE_STRING, requestArgs);
	StreamLabsClient::GetInstance()->SendRequest(request);
	//TODO refactor this, reply should be accessible here
	StreamLabsClient::GetInstance()->ReceiveReply();
	delete request;
}

string DummyClassClientImpl::GetString()
{
	json requestArgs;
	requestArgs[OBJ_ID] = id;
	Request* request = new Request(Action::GET_STRING, requestArgs);
	StreamLabsClient::GetInstance()->SendRequest(request);
	//TODO refactor this, reply should be accessible here
	StreamLabsClient::GetInstance()->ReceiveReply();
	delete request;
	return ""; //TODO change this to actual value
}

void DummyClassClientImpl::SetString(string newString)
{
	json requestArgs;
	requestArgs[OBJ_ID] = id;
	requestArgs[STRING] = newString;
	Request* request = new Request(Action::SET_STRING, requestArgs);
	StreamLabsClient::GetInstance()->SendRequest(request);
	//TODO refactor this, reply should be accessible here
	StreamLabsClient::GetInstance()->ReceiveReply();
	delete request;
}

int DummyClassClientImpl::CreateObj()
{
	json requestArgs;
	Request* request = new Request(Action::CREATE_DUMMY_OBJECT);
	StreamLabsClient::GetInstance()->SendRequest(request);
	//TODO refactor this, reply should be accessible here
	StreamLabsClient::GetInstance()->ReceiveReply();
	delete request;
	return 0;
}


/*
TODO check where this should go
json DummyClassClientImpl::GetObj()
{
	json requestArgs;
	requestArgs[OBJ_ID] = id;
	Request* request = new Request(Action::GET_OBJECT, requestArgs);
	StreamLabsClient::GetInstance()->SendRequest(request->ToString());
	//TODO refactor this, reply should be accessible here
	StreamLabsClient::GetInstance()->ReceiveReply();
	delete request;
	return json(); //TODO change this to actual value
}
*/
//TODO assumption just one type of objects
