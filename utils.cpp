#include <Arduino.h>
#include "utils.h"

Utils::Utils() {

}

Utils::~Utils() {

}

char** Utils::tokeniseString(char* input, char* delim) {
	char* token;
	char* c;
	char* ptr = strdup(input);
	int tCount;
	token = strtok_r(ptr, delim, &c);
	while(token != NULL) {
		tCount++;
		token = strtok_r(NULL, delim, &c);
	}
	Serial.print("number of tokens ");
	Serial.println(tCount);
}
