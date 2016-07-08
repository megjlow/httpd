#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "httpd.h"
#include "httpcontext.h"
#include "httprequest.h"
#include "httpresponse.h"


Httpd::Httpd() {;
}

Httpd::~Httpd() {

}

HttpContext* Httpd::processRequest(WiFiClient* client) {
	return NULL;
}

HttpRequest* Httpd::parseRequest(char* input){
	HttpRequest* retval = new HttpRequest(input);
	return retval;
}

HttpResponse* Httpd::createResponse(char* code, int pinValue) {
	HttpResponse* retval = new HttpResponse(code, pinValue);
	return retval;
}

void Httpd::sendResponse(HttpResponse* response) {

}



