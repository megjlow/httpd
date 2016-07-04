#include <Arduino.h>
#include "utils.h"
#include "request.h"

Utils::Utils() {

}

Utils::~Utils() {

}

Tokens* Utils::tokeniseString(char* input, char* delim) {
	Tokens* retval = new Tokens();
	char* token = NULL;
	char* c;

	token = strtok_r(input, delim, &c);
	while(token != NULL) {
		retval->addToken(token);
		token = strtok_r(NULL, delim, &c);
	}
	return retval;
}
