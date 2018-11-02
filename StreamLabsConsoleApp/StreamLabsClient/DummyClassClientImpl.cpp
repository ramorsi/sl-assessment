#include "DummyClassClientImpl.h"

DummyClassClientImpl::DummyClassClientImpl()
{

}
DummyClassClientImpl::DummyClassClientImpl(int id, int integer_value, string string_value) : DummyClass(id, integer_value, string_value)
{}


void DummyClassClientImpl::IncrementInteger()
{
	json requestArgs;
	requestArgs[OBJ_ID] = id_;
	std::unique_ptr<Request> request(new Request(Action::INCREMENT_INTEGER, requestArgs));
	StreamLabsClient::GetInstance()->SendRequest(*request);
	//TODO refactor this, reply should be accessible here
	Response response = StreamLabsClient::GetInstance()->ReceiveReply();
	json responseJson = json::parse(response.GetResponseData());
	this->integer_value_ = responseJson[INTEGER_VALUE];
}

void DummyClassClientImpl::DecrementInteger()
{
	json requestArgs;
	requestArgs[OBJ_ID] = id_;
	std::unique_ptr<Request> request(new Request(Action::DECREMENT_INTEGER, requestArgs));
	StreamLabsClient::GetInstance()->SendRequest(*request);
	//TODO refactor this, reply should be accessible here
	Response response = StreamLabsClient::GetInstance()->ReceiveReply();
	json responseJson = json::parse(response.GetResponseData());
	this->integer_value_ = responseJson[INTEGER_VALUE];
}

int DummyClassClientImpl::GetInteger()
{
	json requestArgs;
	requestArgs[OBJ_ID] = id_;
	std::unique_ptr<Request> request(new Request(Action::GET_INTEGER, requestArgs));
	StreamLabsClient::GetInstance()->SendRequest(*request);
	Response response = StreamLabsClient::GetInstance()->ReceiveReply();
	json responseJson = json::parse(response.GetResponseData());
	return responseJson[INTEGER_VALUE];
}

void DummyClassClientImpl::SetInteger(int newValue)
{
	json requestArgs;
	requestArgs[OBJ_ID] = id_;
	requestArgs[INTEGER_VALUE] = newValue;
	std::unique_ptr<Request> request(new Request(Action::SET_INTEGER, requestArgs));
	StreamLabsClient::GetInstance()->SendRequest(*request);
	Response response = StreamLabsClient::GetInstance()->ReceiveReply();
	json responseJson = json::parse(response.GetResponseData());
	this->integer_value_ = responseJson[INTEGER_VALUE];
}

void DummyClassClientImpl::ReverseString()
{
	json requestArgs;
	requestArgs[OBJ_ID] = id_;
	std::unique_ptr<Request> request(new Request(Action::REVERSE_STRING, requestArgs));
	StreamLabsClient::GetInstance()->SendRequest(*request);
	Response response = StreamLabsClient::GetInstance()->ReceiveReply();
	json responseJson = json::parse(response.GetResponseData());
	this->string_value_ = responseJson[STRING_VALUE];
}

string DummyClassClientImpl::GetString()
{
	json requestArgs;
	requestArgs[OBJ_ID] = id_;
	std::unique_ptr<Request> request(new Request(Action::GET_STRING, requestArgs));
	StreamLabsClient::GetInstance()->SendRequest(*request);
	//TODO refactor this, reply should be accessible here
	Response response = StreamLabsClient::GetInstance()->ReceiveReply();
	json responseJson = json::parse(response.GetResponseData());
	return responseJson[STRING_VALUE];
}

void DummyClassClientImpl::SetString(string newString)
{
	json requestArgs;
	requestArgs[OBJ_ID] = id_;
	requestArgs[STRING_VALUE] = newString;
	std::unique_ptr<Request> request(new Request(Action::SET_STRING, requestArgs));
	StreamLabsClient::GetInstance()->SendRequest(*request);
	Response response = StreamLabsClient::GetInstance()->ReceiveReply();
	json responseJson = json::parse(response.GetResponseData());
	this->string_value_ = responseJson[STRING_VALUE];
}

int DummyClassClientImpl::CreateObj()
{
	json requestArgs;
	std::unique_ptr<Request> request(new Request(Action::CREATE_DUMMY_OBJECT));
	StreamLabsClient::GetInstance()->SendRequest(*request);
	Response response = StreamLabsClient::GetInstance()->ReceiveReply();
	json responseData = json::parse(response.GetResponseData());
	return responseData[OBJ_ID];
}



DummyClass* DummyClassClientImpl::GetObj(int id)
{
	json requestArgs;
	requestArgs[OBJ_ID] = id;
	std::unique_ptr<Request> request(new Request(Action::GET_OBJECT, requestArgs));
	StreamLabsClient::GetInstance()->SendRequest(*request);
	Response response = StreamLabsClient::GetInstance()->ReceiveReply();
	json responseData = json::parse(response.GetResponseData());
	int objId = responseData[OBJ_ID];
	int a = responseData[INTEGER_VALUE];
	string str = responseData[STRING_VALUE];
	DummyClass* dummy = new DummyClassClientImpl(objId, a, str);
	return dummy;
}

//TODO assumption just one type of objects
