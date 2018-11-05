# StreamBase 

A client/server application to manage data on a Windows system. Client and Server connect via namedpipes. The app supports an echo feature, where the client can send text to the server and receive it back. The app also allows clients to create objects server side, retrieve them and perfom functions on them.

## General Code Structure

The code comprises three VS projects; StreamLabsServer, StreamLabsClient, StreamLabsCommon. 

### StreamLabsServer
The server project holds all code related to the server (starting the server, recieving and logging requests, sending replies,...etc). The server also implements
the DummyClass which is the object upon which the clients perform functions. 

### StreamLabsClient
The client project holds all code related to the server (connecting the server, sending requests and receiving replies,...etc)

### StreamLabsCommon
The common project holds all code that is common to both the client and server. 
#### DummyClass
Is an interface implemented by both the client and server. The server implementation holds the actual logic of the functions. The client
implementation holds requests sent to the server to actually perform the functions.
#### Request and Reply
These are two classes that are used to format requests and replies. Requests and replies are expected to 
be formatted as json strings. Each function dictates specific parameters.
#### Constants.h
Holds constant parameters accessible by the client and server such as buffer size and parameter names
#### StreamLabsException.h
Is a custom exception class
 
## Limitations
- Maximum number of objects created should not exceed int value
- Maximum allowed message size is 512 characters. 
- Only ASCII characters are used.
- Only one type of object is known to the client and server (DummyClass)
- No distinguishing between clients. Any connected client has access to objects created by other clients
- Pipe name is hardcoded. Can be easily modified to be set during runtime.

## Possible Enhancements
- Add support for different types of objects. Clients should be able to specify the object type
- Pretify the console display


## Getting Started

The executables for both the client and server can be found in the binaries folder.



## Authors

* **Rana Morsi** - [StreamBase](https://github.com/ramorsi/sl-assessment)