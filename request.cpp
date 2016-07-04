#include "Arduino.h"
#include "request.h"
#include "tokens.h"
#include "utils.h"


Request::Request(char* input) {
	this->nHeaders = 0;
	this->headerArray = new Headers();
	Utils* utils = new Utils();
	Tokens* headers = utils->tokeniseString(input, "\r\n");
	for(int i=0; i<headers->count(); i++) {
		if(strncmp(headers->token(i), "GET", 3) == 0 || strncmp(headers->token(i), "POST", 4) == 0) {
			// this is the request - METHOD URL PROTOCOL
			Tokens* urlTokens = utils->tokeniseString(headers->token(i), " ");
			this->requestMethod = urlTokens->token(0);
			this->requestUrl = urlTokens->token(1);
			delete urlTokens;
		}
		else {
			Tokens *header = utils->tokeniseString(headers->token(i), ":");
			Header* h = new Header(header->token(0), header->token(1));
			this->headerArray->addHeader(h);
			delete header;
		}
	}

	//delete headers;
	delete utils;
}

Request::~Request() {
	delete this->headerArray;
}

void Request::parseUrl() {

}

int Request::getPinNumber() {
	return 0;
}

int Request::getPinSetting() {
	return 0;
}


int Request::headerCount() {
	//return this->nHeaders;
}

Header* Request::getHeader(int n) {
	//return this->headers[n];
}

Header* Request::getHeader(char* name) {
	//return this->headers[0];
}

char* Request::getRequestUrl() {
	return this->requestUrl;
}

char* Request::getRequestMethod() {
	return this->requestMethod;
}
