#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "httpd.h"
#include "httpcontext.h"
#include "request.h"
#include "response.h"


Httpd::Httpd() {;
}

Httpd::~Httpd() {

}

HttpContext* Httpd::processRequest(WiFiClient* client) {
	return NULL;
}

Request* Httpd::parseRequest(char* input){
	Request* retval = new Request(input);
	return retval;
}

Response* Httpd::createResponse(char* code, int pinValue) {
	Response* retval = new Response(code, pinValue);
	return retval;
}

void Httpd::sendResponse(Response* response) {

}



