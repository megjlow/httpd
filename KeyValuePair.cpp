#include "KeyValuePair.h"
#include <Arduino.h>

KeyValuePair::KeyValuePair(char* key, char* value) {
	this->m_Key = strdup(key);
	this->m_Value = strdup(value);
}

KeyValuePair::~KeyValuePair() {
	free(this->m_Key);
	free(this->m_Value);
}

char* KeyValuePair::key() {
	return m_Key;
}

char* KeyValuePair::value() {
	return m_Value;
}
