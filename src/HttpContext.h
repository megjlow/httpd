#ifndef httpcontext_h
#define httpcontext_h


#include <Arduino.h>


#include <HttpRequest.h>
#include <HttpResponse.h>
#include <sockets/Socket.h>

class HttpContext {
public:
	HttpContext(httpd::sockets::Socket* client);
	~HttpContext();
	HttpRequest* request();
	HttpResponse* response();
private:
	httpd::sockets::Socket* _socket;
	HttpRequest* _request;
	HttpResponse* _response;
	char* method;
	char* url;
	char* setRequestUrl(char* url);
};

#endif
