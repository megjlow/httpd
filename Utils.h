#ifndef utils_h
#define utils_h

#include <Arduino.h>
#include "Tokens.h"

class Utils {
public:
	Utils();
	~Utils();
	Tokens* tokeniseString(char* input, char* token);
	Tokens* tokeniseHeader(char* header, char* delim);
};

#endif
