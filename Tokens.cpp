#include <Arduino.h>
#include "Tokens.h"

Tokens::Tokens() {
	// for the moment start with 50 but we could start with 10 and add another 10 each time it's required
	this->tokens = (char**)calloc(50, sizeof(char*));
	this->nTokens = 0;
}

Tokens::~Tokens() {
	for(int i=0; i<this->nTokens; i++) {
		free(this->tokens[i]);
	}
	free(this->tokens);
}

int Tokens::count() {
	return nTokens;
}

void Tokens::addToken(char* token) {
	this->tokens[this->nTokens] = strdup(token);
	this->nTokens++;
}

char* Tokens::token(int n) {
	char* retval = NULL;
	if(n < this->nTokens) {
		retval = this->tokens[n];
	}
	return retval;
}
