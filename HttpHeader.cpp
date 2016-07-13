#include <Arduino.h>

#include "HttpHeader.h"


// Host: 192.168.2.102
// User-Agent: Mozilla/5.0 (X11; Fedora; Linux x86_64; rv:47.0) Gecko/20100101 Firefox/47.0
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
// Accept-Language: en-US,en;q=0.5
// Accept-Encoding: gzip, deflate
// Connection: keep-alive
// Pragma: no-cache
// Cache-Control: no-cache
 

HttpHeader::HttpHeader(char* key, char* value) {
	this->m_Key = strdup(key);
	this->m_Value = strdup(value);
}

HttpHeader::~HttpHeader() {
	if(this->m_Key) free(this->m_Key);
	if(this->m_Value) free(this->m_Value);
}

char* HttpHeader::key() {
	return this->m_Key;
}

char* HttpHeader::value() {
	return this->m_Value;
}

char* HttpHeader::toString() {
	return NULL;
	/*
	char* retval;
	size_t size = strlen(m_Key) + strlen(m_Value) + 2;
	retval = (char*) calloc(size, sizeof(char*));
	strcat(retval, m_Key);
	strcat(retval, ":");
	strcat(retval, m_Value);
	return retval;
	*/
}
