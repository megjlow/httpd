#include "Arduino.h"
#include "request.h"
#include "tokens.h"
#include "utils.h"


Request::Request(char* input) {
	this->pinNumber = 0;
	this->pinSetting = 0;
	this->nHeaders = 0;
	this->requestUrl = NULL;
	this->requestMethod = NULL;
	this->headerArray = new Headers();
	Utils* utils = new Utils();
	Tokens* headers = utils->tokeniseString(input, "\r\n");
	for(int i=0; i<headers->count(); i++) {
		if(strncmp(headers->token(i), "GET", 3) == 0 || strncmp(headers->token(i), "POST", 4) == 0) {
			// this is the request - METHOD URL PROTOCOL
			Tokens* urlTokens = utils->tokeniseString(headers->token(i), " ");
			this->requestMethod = strdup(urlTokens->token(0));
			char* url = strdup(urlTokens->token(1));
			this->setRequestUrl(url);
			delete urlTokens;
		}
		else {
			Tokens *header = utils->tokeniseString(headers->token(i), ":");
			Header* h = new Header(header->token(0), header->token(1));
			this->headerArray->addHeader(h);
			delete header;
		}
	}

	delete headers;
	delete utils;
}

Request::~Request() {
	delete this->headerArray;
	if(this->requestMethod) free(this->requestMethod);
	if(this->requestUrl) free(this->requestUrl);
}

void Request::parseUrl() {

}

int Request::getPinNumber() {
	return this->pinNumber;
}

int Request::getPinSetting() {
	return this->pinSetting;
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

char* Request::setRequestUrl(char* url) {
	char* retval = "200";
	this->requestUrl = url;
	char* ptr = strdup(url);
	Utils* u = new Utils();
	Tokens *t = u->tokeniseString(ptr, "/");
	if(strcmp(this->requestMethod, "POST") == 0) {
		if(t->count() >= 2) {
			if(strncmp(t->token(0), "gpio", 4) == 0) {
				// should be a pin number
				String s = String(t->token(0));
				int i = s.indexOf("gpio");
				String x = s.substring(4);
				this->pinNumber = x.toInt();
			}
			String s = String(t->token(1));
			this->pinSetting = s.toInt();
		}
	}
	else {
		String s = String(t->token(0));
		int i = s.indexOf("gpio");
		String x = s.substring(4);
		this->pinNumber = x.toInt();
	}
	free(ptr);
	delete t;
	return retval;
}

char* Request::getRequestMethod() {
	return this->requestMethod;
}
