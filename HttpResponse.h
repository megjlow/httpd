#ifndef httpresponse_h
#define httpresponse_h

#include <Arduino.h>
#include "FS.h"
#include "ESP8266WiFi.h"

class HttpResponse{
public:
	HttpResponse(char* code, int pinValue);
	~HttpResponse();
	char* getResponse();
	void sendFile(WiFiClient client, File f);
private:
	char* code;
	int pinValue;
	char* retval;
};

#endif
