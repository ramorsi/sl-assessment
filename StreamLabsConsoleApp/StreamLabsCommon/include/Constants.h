#pragma once
#define ACTION "action"
#define DATA "data"
#define INTEGER_VALUE "integer_value"
#define OBJ_ID "obj_id"
#define RESPONSE "response"
#define REQUEST_ARGS "request_args"
#define STATUS_CODE "status_code"
#define STRING_VALUE "string_value"

#define BUFSIZE 512 //Maximum size of messages sent
#define PIPE_NAME "\\\\.\\pipe\\streamlabs_pipe_name"  //This is a hardcoded pipename used by
													   //both the client and server.  Can be
													   //easily changed to be taken as input
													   //from the user

