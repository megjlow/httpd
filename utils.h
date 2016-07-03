#ifndef utils_h
#define utils_h

#include <Arduino.h>

class Utils {
public:
	Utils();
	~Utils();
	char** tokeniseString(char* input, char* token);
};

#endif
