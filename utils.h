#ifndef utils_h
#define utils_h

#include <Arduino.h>
#include "tokens.h"

class Utils {
public:
	Utils();
	~Utils();
	Tokens* tokeniseString(char* input, char* token);
};

#endif