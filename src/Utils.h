#ifndef utils_h
#define utils_h

#include <Arduino.h>
#include "Array.h"

class Utils {
public:
	Utils();
	~Utils();
	//Tokens* tokeniseString(char* input, char* token);
	//Tokens* tokeniseHeader(char* header, char* delim);
	static Array<char>* tokeniseString(char* input, char* token);
	static Array<char>* tokeniseHeader(char* input, char* token);
	static void urlDecode(char* dst, const char* src);
	static char* strdup(char* input);
	static void printFreeHeap();
};

#endif
