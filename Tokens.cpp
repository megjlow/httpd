#include <Arduino.h>
#include "Tokens.h"

Tokens::Tokens() {
	this->tokenArray = new char*[30];
	this->nTokens = 0;
}

Tokens::~Tokens() {
	for(int i=0; i<this->nTokens; i++) {
		delete this->tokenArray[i];
	}
	delete[] this->tokenArray;
}

int Tokens::count() {
	return this->nTokens;
}

void Tokens::addToken(char* token) {
	// copy to "new"ed char array, Array will "delete" everything
	char* buf = new char[strlen(token) + 1];
	memcpy(buf, token, strlen(token));
	buf[strlen(token)] = NULL;
	this->tokenArray[nTokens] = buf;
	this->nTokens++;
}

char* Tokens::getToken(int n) {
	char* retval = NULL;
	if(n < this->nTokens) {
		retval = this->tokenArray[n];
	}
	return retval;
}
