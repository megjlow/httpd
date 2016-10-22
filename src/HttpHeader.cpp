#include <Arduino.h>

#include "HttpHeader.h"

HttpHeader::HttpHeader(char* key, char* value) {
	this->_key = strdup(key);
	this->_value = strdup(value);
}

HttpHeader::HttpHeader(HttpHeader* header) {
	this->_key = strdup(header->key());
	this->_value = strdup(header->value());
}

HttpHeader::~HttpHeader() {
	free(this->_key);
	free(this->_value);
}

char* HttpHeader::key() {
	return this->_key;
}

char* HttpHeader::value() {
	return this->_value;
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
