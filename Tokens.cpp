#include <Arduino.h>
#include "Tokens.h"
#include "Array.h"

Tokens::Tokens(): Array() {
}


int Tokens::count() {
	return Array::count();
}

void Tokens::addToken(char* token) {
	// copy to "new"ed char array, Array will "delete" everything
	char* buf = new char[strlen(token) + 1];
	memcpy(buf, token, strlen(token));
	buf[strlen(token)] = NULL;
	Array::add((void*) buf);
}

char* Tokens::getToken(int n) {
	return (char*) Array::get(n);
}
