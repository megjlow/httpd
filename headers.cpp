#include<Arduino.h>
#include "request.h"

Headers::Headers() {
	this->nHeaders = 0;
	this->headerArray = (Header**) calloc(10, sizeof(Header*));
}

Headers::~Headers() {
	for(int i=0; i<nHeaders; i++) {
		delete this->headerArray[i];
	}
	free(headerArray);
}

void Headers::addHeader(Header* header) {
	this->headerArray[nHeaders] = header;
	this->nHeaders++;
}

Header* Headers::getHeader(int n) {
	Header* retval = NULL;
	if(n <= this->nHeaders) {
		retval = this->headerArray[n];
	}
	return retval;
}

int Headers::count() {
	return this->nHeaders;
}
