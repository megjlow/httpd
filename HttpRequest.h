#ifndef httprequest_h
#define httprequest_h

#include <Arduino.h>

#include "HttpHeader.h"
#include "HttpHeaders.h"
#include "RequestParams.h"

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
private:
	HttpHeaders* headerArray;
	RequestParams* params;
	char* requestMethod;
	char* requestUrl;
	int pinNumber;
	int pinSetting;
	void setRequestUrl(char* url);
};

#endif
