#ifndef httprequest_h
#define httprequest_h

#include <Arduino.h>

#include "HttpHeader.h"
#include "HttpHeaders.h"
#include "RequestParameters.h"

class HttpRequest {
public: 
	HttpRequest(char* input);
	~HttpRequest();
	int headerCount();
	HttpHeader* getHeader(char* name);
	HttpHeader* getHeader(int n);
	char* getRequestUrl();
	char* getRequestMethod();
	void parseUrl();
	int getPinNumber();
	int getPinSetting();
	char* getParameter(char* name);
private:
	HttpHeaders* headerArray;
	RequestParameters* requestParameters;
	char* requestMethod;
	char* requestUrl;
	int pinNumber;
	int pinSetting;
	void setRequestUrl(char* url);
};

#endif
