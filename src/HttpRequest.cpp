#include "HttpRequest.h"

#include <Arduino.h>
#include <sockets/Socket.h>
#include <HttpHeader.h>
#include <Utils.h>

using namespace httpd::sockets;

HttpRequest::HttpRequest(Socket* socket) {
	this->_url = NULL;
	this->_method = NULL;
	this->_headers = new Array<HttpHeader>();
	this->_parameters = new Array<KeyValuePair>();
	this->_parseSuccess = true;
	char* buffer = new char[1024];
	delay(10);
	int bytesavailable = socket->available();
	if(bytesavailable > 0) {
		int read = socket->readBytes(buffer, bytesavailable);
		buffer[bytesavailable] = '\0';
		ParseRequest(buffer);
	}
	else {
		this->_parseSuccess = false;
		Serial.println("XXXXXXXXXXXXXXXXXXX  Empty Request XXXXXXXXXXXXXXXXXXXXXX");
	}
	delete buffer;
	delay(1);
}

HttpRequest::~HttpRequest() {
	delete this->_headers;
	delete this->_parameters;
	free(this->_method);
	free(this->_url);
}

bool HttpRequest::parseSuccess() {
	return this->_parseSuccess;
}

void HttpRequest::parseMethod(char* header) {
	Array<char>* tokens = Utils::tokeniseString(header, " ");
	if(tokens->count() >= 2) {
		this->_method = strdup(tokens->get(0));
		this->_url = strdup(tokens->get(1));
	}
	delete tokens;
}

void HttpRequest::parseHeader(char* header) {
	Array<char>* tokens = Utils::tokeniseString(header, ": ");
	if(tokens->count() == 2) {
		HttpHeader* h = new HttpHeader(tokens->get(0), tokens->get(1));
		this->_headers->add(h);
	}
	delete tokens;
}

void HttpRequest::ParseRequest(char* request) {
	Array<char>* headers = Utils::tokeniseString(request, "\r\n");
	for(int i=0; i<headers->count(); i++) {
		if(strncmp(headers->get(i), "GET", 3) == 0 || strncmp(headers->get(i), "POST", 4) == 0) {
			parseMethod(headers->get(i));
		}
		else {
			// if it contains a : it's a header?
			if(strchr(headers->get(i), ':') != NULL) {
				parseHeader(headers->get(i));
			}
			else { // else it has to be request parameters?
				Array<char>* t = Utils::tokeniseString(headers->get(i), "&");
				for(int j=0; j<t->count(); j++) {
					Array<char>* pair = Utils::tokeniseString(t->get(j), "=");
					if(pair->count() == 2) {
						KeyValuePair* kvp = new KeyValuePair(pair->get(0), pair->get(1));
						this->_parameters->add(kvp);
					}
				};
				delete t;
			}
		}
	}

	delete headers;
}


int HttpRequest::headerCount() {
	this->_headers->count();
}

HttpHeader* HttpRequest::getHeader(int n) {
	//return this->_headers[n];
}

char* HttpRequest::getHeader(char* name) {
	char* retval = NULL;
	for(int i=0; i<this->_headers->count(); i++) {
		if(strcmp(this->_headers->get(i)->key(), name) == 0) {
			retval = this->_headers->get(i)->value();
		}
	}
	return retval;
}

char* HttpRequest::url() {
	return this->_url;
}

char* HttpRequest::method() {
	return this->_method;
}

char* HttpRequest::getParameter(char* name) {
	char* retval = NULL;
	KeyValuePair* pair = this->_parameters->get(name);
	if(pair != NULL) {
		retval = pair->value();
	}
	return retval;
}
