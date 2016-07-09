#ifndef httpcontext_h
#define httpcontext_h


#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "httprequest.h"
#include "httpresponse.h"
#include "HttpHeaders.h"

class HttpContext {
public:
	HttpContext(WiFiClient* client);
	~HttpContext();
private:
	HttpHeaders* headerArray;
	int nHeaders;
	char* requestMethod;
	char* requestUrl;
	int pinNumber;
	int pinSetting;
	char* setRequestUrl(char* url);
};

#endif
