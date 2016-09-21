#ifndef httpresponse_h
#define httpresponse_h

#include <Arduino.h>
#include <sockets/Socket.h>
#include <HttpHeader.h>
#include <Array.h>

class HttpResponse{
public:
	HttpResponse(httpd::sockets::Socket* socket);
	~HttpResponse();
	void setResponseCode(char* code);
	void addHeader(HttpHeader* header);
	void addHeader(char* key, char* value);
	void setBody(char* body);
	void setBody(String body);
	void sendResponse();
	char* pingResponse();
private:
	httpd::sockets::Socket* _socket;
	Array<HttpHeader>* _headers;
	char* _code;
	char* _body;
	int pinValue;
	char* retval;
};

#endif
