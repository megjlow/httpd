#ifndef tokens_h
#define tokens_h

#include <Arduino.h>
#include "Array.h"

class Tokens: public Array {
public:
	Tokens();
	int count();
	char* getToken(int n);
	void addToken(char* token);
};

#endif
