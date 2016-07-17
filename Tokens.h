#ifndef tokens_h
#define tokens_h

#include <Arduino.h>

class Tokens {
public:
	Tokens();
	~Tokens();
	int count();
	char* getToken(int n);
	void addToken(char* token);
private:
	char** tokenArray;
	int nTokens;
};

#endif
