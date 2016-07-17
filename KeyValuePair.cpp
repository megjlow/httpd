#include "KeyValuePair.h"
#include <Arduino.h>

KeyValuePair::KeyValuePair(char* key, char* value) {
	Serial.println("KeyValuePair construct");
	this->m_Key = strdup(key);
	this->m_Value = strdup(value);
}

KeyValuePair::~KeyValuePair() {
	Serial.println("KeyValuePair destruct");
	free(this->m_Key);
	free(this->m_Value);
}

char* KeyValuePair::key() {
	return m_Key;
}

char* KeyValuePair::value() {
	return m_Value;
}
