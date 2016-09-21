#ifndef httprequest_h
#define httprequest_h

#include <Arduino.h>
#include <HttpHeader.h>
#include <KeyValuePair.h>
#include <Array.h>
#include <sockets/Socket.h>

class HttpRequest {
public: 
	HttpRequest(httpd::sockets::Socket* client);
	~HttpRequest();
	int headerCount();
	char* getHeader(char* name);
	HttpHeader* getHeader(int n);
	char* url();
	char* method();
	void parseUrl();
	char* getParameter(char* name);
	bool parseSuccess();
private:
	void ParseRequest(char* request);
	void parseMethod(char* header);
	void parseHeader(char* header);
	bool _parseSuccess;
	Array<HttpHeader>* _headers;
	Array<KeyValuePair>* _parameters;
	char* _method;
	char* _url;
};

#endif
