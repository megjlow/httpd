#include "RequestParams.h"

RequestParams::RequestParams() {
	this->params = new KeyValuePair*[30];
	this->nParams = 0;
}

RequestParams::~RequestParams() {
	for(int i=0; i<this->nParams; i++) {
		delete this->params[i];
	}
	delete[] this->params;
}

char* RequestParams::getRequestParam(char* name) {
	char* retval = NULL;
	for(int i=0; i<this->nParams; i++) {
		if(strcmp(this->params[i]->key(), name) == 0) {
			retval = this->params[i]->value();
		}
	}
	return retval;
}
