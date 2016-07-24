#include "RequestParameters.h"
#include "Utils.h"

RequestParameters::RequestParameters() {
	this->params = new KeyValuePair*[30];
	this->nParams = 0;
}

RequestParameters::~RequestParameters() {
	for(int i=0; i<this->nParams; i++) {
		delete this->params[i];
	}
	delete[] this->params;
}

void RequestParameters::addRequestParameter(char* value) {
	Serial.println(value);
	if(strchr(value, '=') != NULL) {
		Utils* utils = new Utils();
		Tokens* tokens = utils->tokeniseString(value, "=");
		if(tokens->count() >= 2) {
			char* key = new char[strlen(tokens->getToken(0)) + 1];
			char* value = new char[strlen(tokens->getToken(1)) + 1];
			memset(key, 0, sizeof(key));
			memset(value, 0, sizeof(value));
			utils->urlDecode(key, tokens->getToken(0));
			utils->urlDecode(value, tokens->getToken(1));
			KeyValuePair* kvp = new KeyValuePair(key, value);
			this->params[nParams] = kvp;
			nParams++;
			delete key;
			delete value;
		}
		delete tokens;
		delete utils;
	}
}

char* RequestParameters::getRequestParameter(char* name) {
	char* retval = NULL;
	for(int i=0; i<this->nParams; i++) {
		if(strcmp(this->params[i]->key(), name) == 0) {
			retval = this->params[i]->value();
		}
	}
	return retval;
}