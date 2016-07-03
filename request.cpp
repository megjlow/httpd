#include "Arduino.h"
#include "request.h"


Request::Request(char* input) {
	this->nHeaders = 0;
	char* ptr = strdup(input);
	char* token = NULL;
	char* i;
	int count = 0;
	
	// count the number of headers
	token = strtok_r(ptr, "\r\n", &i);
	while(token != NULL) {
		if(strncmp(token, "GET", 3) != 0 && strncmp(token, "POST", 4) != 0) { // not going to count the request
			this->nHeaders++;
		}
		token = strtok_r(NULL, "\r\n", &i);
	}
	free(ptr);
	
	this->headers = new Header*[nHeaders + 1];
	token = strtok_r(input, "\r\n", &i);
	while(token != NULL) {
		if(strncmp(token, "GET", 3) != 0 && strncmp(token, "POST", 4) != 0) {
			this->headers[count] = new Header(token);
			count++;
		}
		else {
			// this is the request METHOD PATH PROTOCOL
			char* d;
			char* t = strtok_r(token, " ", &d);
			this->requestMethod = strdup(t);
			this->requestUrl = strdup(strtok_r(NULL, "", &d));
		}
		token = strtok_r(NULL, "\r\n", &i);
	}
}

Request::~Request() {
	for(int i=0; i<nHeaders; i++) {
		delete this->headers[i];
	}
	delete(this->headers);
}


int Request::headerCount() {
	return this->nHeaders;
}

Header* Request::getHeader(int n) {
	return this->headers[n];
}

Header* Request::getHeader(char* name) {
	return this->headers[0];
}

char* Request::getRequestUrl() {
	return this->requestUrl;
}

char* Request::getRequestMethod() {
	return this->requestMethod;
}
