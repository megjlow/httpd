#include <Arduino.h>
#include "request.h"


// Host: 192.168.2.102
// User-Agent: Mozilla/5.0 (X11; Fedora; Linux x86_64; rv:47.0) Gecko/20100101 Firefox/47.0
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
// Accept-Language: en-US,en;q=0.5
// Accept-Encoding: gzip, deflate
// Connection: keep-alive
// Pragma: no-cache
// Cache-Control: no-cache
 

Header::Header(char* input) {
	char* ptr = strdup(input);
	char* token = NULL;
	char* i;
	token = strtok_r(ptr, ":", &i);
	if(token != NULL) {
		this->m_Key = strdup(token);
		token = strtok_r(NULL, ":", &i);
		if(token != NULL) {
			this->m_Value = strdup(token);
		}
	}
	free(ptr);
}

Header::~Header() {
	if(this->m_Key) free(this->m_Key);
	if(this->m_Value) free(this->m_Value);
}

char* Header::key() {
	return this->m_Key;
}

char* Header::value() {
	return this->m_Value;
}
