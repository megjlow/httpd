#ifndef utils_h
#define utils_h

#include <Arduino.h>
#include "Array.h"

class Utils {
public:
	Utils();
	~Utils();
	static Array<char>* tokeniseString(char* input, char* token);
	static Array<char>* tokeniseHeader(char* input, char* token);
	static void urlDecode(char* dst, const char* src);
	static void urlEncode(char* dst, const char* src);
	static char* strdup(char* input);
	static void printFreeHeap();
	static void dumpWsMessage(char* message);
};

#endif
