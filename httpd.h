#ifndef httpd_h
#define httpd_h

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "httpcontext.h"
#include "request.h"
#include "response.h"

class Httpd {
public:
	Httpd();
	~Httpd();
	Request* parseRequest(char *input);
	Response* createResponse(char* code, int pinValue);
	void sendResponse(Response* response);
	HttpContext* processRequest(WiFiClient* client);
};

#endif
