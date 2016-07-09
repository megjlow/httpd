#ifndef httpd_h
#define httpd_h

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "httpcontext.h"
#include "httprequest.h"
#include "httpresponse.h"

class Httpd {
public:
	Httpd();
	~Httpd();
	HttpRequest* parseRequest(char *input);
	HttpResponse* createResponse(char* code, int pinValue);
	void sendResponse(HttpResponse* response);
	HttpContext* processRequest(WiFiClient* client);
};

#endif
