#include <Arduino.h>

#include "HttpHeader.h"

HttpHeader::HttpHeader(char* key, char* value) {
	this->m_Key = strdup(key);
	this->m_Value = strdup(value);
}

HttpHeader::~HttpHeader() {
	free(this->m_Key);
	free(this->m_Value);
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
