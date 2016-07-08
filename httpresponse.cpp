#include <Arduino.h>

#include "httpresponse.h"

HttpResponse::HttpResponse(char* code, int pinValue) {
	this->code = code;
	this->pinValue = pinValue;
}

HttpResponse::~HttpResponse() {
}

char* HttpResponse::getResponse() {
	char* retval;
	retval = (char*) calloc(200, sizeof(char));
	strcat(retval, "HTTP/1.1 ");
	if(strcmp(this->code, "200") == 0) {
		strcat(retval, "200 OK\r\n");
	}
	strcat(retval, "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n\r\n{\"value\":\"");
	char c[2] = {'\0','\0'};
	c[0] = this->pinValue + '0';
	strcat(retval, c);
	strcat(retval, "\"}");
	return retval;
}
