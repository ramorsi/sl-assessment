// This class holds server code. It is responsible for starting the server thread which
// continues to listen for incoming requests from clients. A multithreaded design is used, 
// where a thread is created per each client connection.
#include <windows.h> 
#include <stdio.h> 
#include <tchar.h>
#include <strsafe.h>
#include <string>
#include <map>
#include <iostream>
#include <time.h>

#include "DummyClass.h"
#include "nlohmann/json.hpp"
#include "Constants.h"
#include "Request.h"
#include "Response.h"
#include "DummyClassServerImpl.h"
#include "StreamLabsExeption.h"

using json = nlohmann::json;
using namespace std;

class StreamLabsServer {
	static StreamLabsServer* instance; //Singleton Server instance
	StreamLabsServer();
private:
	map<int, DummyClass*> customObjects; //Map to hold all objects created by clients so far.
										 //The key is the id while the value is a pointer to 
										//the created object
	map<time_t, Request> requestLog;
public:
	~StreamLabsServer();

	static StreamLabsServer* GetInstance() {
		if (!instance)
			instance = new StreamLabsServer;
		return instance;
	}
	//Creates a duplex named pipe. Waits for incoming client connections. Creates a thread
	//to handle each connecetion.
	int StartServer();

	//Returns the object with the input id. A custom StreamLabsException is thrown if no 
	// object in the customObjects map has that id
	DummyClass* GetObj(int id);

	//Creates a new instance of the Dummy Class and adds an entry to the customObjects map. 
	// The response states the status of response as well as the actual response data. Ex:
	// {"response":"{\"obj_id\":0}","status_code":0}
	Response CreateDummyObjectHandler();

	//Decrements the integer value of a particular dummy object. The input request args holds
	//parameters specific to the request. ex: {"action":2,"request_args":{"obj_id":0}}. The 
	//action parameter is set using an enum where each action maps to an integer value and 
	//the object id refers to the object instance of interest.
	Response DecrementIntegerHandler(json requestArgs);

	//Gets the integer value of a particular dummy instance. The input request args holds the
	//parameters specific to the request. Ex:	{"action":3,"request_args":{"obj_id":0}}
	Response GetIntegerHandler(json requestArgs);

	//Gets the string value of a particular dummy instance.
	Response GetStringHandler(json requestArgs);

	//Increments the integer value of a particular dummy instance.
	Response IncrementIntegerHandler(json requestArgs);

	//Reveres the string value of a particular dummy instance.
	Response ReverseStringHandler(json requestArgs);

	//Sets the integer value of a particular dummy instance.
	Response SetIntegerHandler(json requestArgs);

	//Sets the string value of a particular dummy instance using the value in the input json.
	Response SetStringHandler(json requestArgs);

	//Returns the string representation of a particular dummy instance.
	Response GetObjHandler(json requestArgs);

	//Retuns an echo of the text recieved.
	Response EchoHandler(json requestArgs);

	void LogRequest(Request request);

	//A thread instance to handle the connection of one client
	static DWORD WINAPI InstanceThread(LPVOID lpvParam);

	//Parses the request sent by the client and encapsulates it in to a "Request" object.
	//Based on the action set in the request, one of the handler functions is called.
	static Response GetAnswerToRequest(char* pchRequest);
};

