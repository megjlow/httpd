#include <Arduino.h>

#include "HttpResponse.h"

HttpResponse::HttpResponse(char* code, int pinValue) {
	this->code = strdup(code);
	this->pinValue = pinValue;
}

HttpResponse::~HttpResponse() {
	free(this->code);
}

char* HttpResponse::getResponse() {
	char* retval = new char[400];
	strcat(retval, "HTTP/1.1 ");
	if(strcmp(this->code, "200") == 0) {
		strcat(retval, "200 OK\r\n");
	}
	strcat(retval, "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n\r\n{\"value\":\"");
	char c[2] = {'\0','\0'};
	c[0] = this->pinValue + '0';
	strcat(retval, c);
	strcat(retval, "\"}");
	strcat(retval, "\0");
	return retval;
}
