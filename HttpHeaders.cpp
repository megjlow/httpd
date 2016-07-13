#include<Arduino.h>

#include "HttpHeaders.h"
#include "HttpHeader.h"

HttpHeaders::HttpHeaders() {
	this->nHeaders = 0;
	this->headerArray = (HttpHeader**) calloc(30, sizeof(HttpHeader*));
}

HttpHeaders::~HttpHeaders() {
	for(int i=0; i<nHeaders; i++) {
		delete this->headerArray[i];
	}
	free(headerArray);
}

void HttpHeaders::addHeader(HttpHeader* header) {
	this->headerArray[nHeaders] = header;
	this->nHeaders++;
}

HttpHeader* HttpHeaders::getHeader(int n) {
	HttpHeader* retval = NULL;
	if(n <= this->nHeaders) {
		retval = this->headerArray[n];
	}
	return retval;
}

int HttpHeaders::count() {
	return this->nHeaders;
}
