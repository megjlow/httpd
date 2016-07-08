#ifndef httpcontext_h
#define httpcontext_h


#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "httprequest.h"
#include "httpresponse.h"

class HttpContext {
public:
	HttpContext(WiFiClient* client);
	~HttpContext();
};

#endif
