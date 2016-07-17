#include<Arduino.h>

#include "HttpHeaders.h"
#include "HttpHeader.h"
#include "Array.h"

HttpHeaders::HttpHeaders() {
	this->nHeaders = 0;
	this->headerArray = new HttpHeader*[30];
}

HttpHeaders::~HttpHeaders() {
	for(int i=0;i<this->nHeaders; i++) {
		delete this->headerArray[i];
	}
	delete[] this->headerArray;
}

void HttpHeaders::add(HttpHeader* header) {
	this->headerArray[nHeaders] = header;
	this->nHeaders++;
}

HttpHeader* HttpHeaders::get(int n) {
	HttpHeader* retval = NULL;
	if(n <= this->nHeaders) {
		return this->headerArray[n];
	}
	return retval;
}

int HttpHeaders::count() {
	return this->nHeaders;
}
