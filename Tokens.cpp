#include <Arduino.h>
#include "Tokens.h"

Tokens::Tokens() {
	this->tokenArray = new char*[30];
	this->nTokens = 0;
}

Tokens::~Tokens() {
	for(int i=0; i<this->nTokens; i++) {
		free(this->tokenArray[i]);
	}
	delete this->tokenArray;
}

int Tokens::count() {
	return this->nTokens;
}

void Tokens::addToken(char* token) {
	this->tokenArray[nTokens] = strdup(token);
	this->nTokens++;
}

char* Tokens::getToken(int n) {
	char* retval = NULL;
	if(n < this->nTokens) {
		retval = this->tokenArray[n];
	}
	return retval;
}
