#include <Arduino.h>

#include "HttpResponse.h"

HttpResponse::HttpResponse(char* code, int pinValue) {
	this->retval = NULL;
	this->code = strdup(code);
	this->pinValue = pinValue;
}

HttpResponse::~HttpResponse() {
	free(this->code);
	if(this->retval != NULL) {
		delete retval;
	}
}

char* HttpResponse::getResponse() {
	this->retval = new char[400];
	for(int i=0; i<400; i++) {
		this->retval[i] = '\0';
	}
	//char* retval = new char[200];
	strcat(this->retval, "HTTP/1.1 ");
	if(strcmp(this->code, "200") == 0) {
		strcat(this->retval, "200 OK\r\n");
	}
	strcat(this->retval, "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n\r\n{\"value\":\"");
	char c[2] = {'\0','\0'};
	c[0] = this->pinValue + '0';
	strcat(this->retval, c);
	strcat(this->retval, "\"}");
	strcat(this->retval, "\0");
	return this->retval;
}
