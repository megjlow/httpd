#include "HttpRequest.h"

#include "Arduino.h"
#include "HttpHeader.h"
#include "HttpHeaders.h"
#include "Tokens.h"
#include "Utils.h"


HttpRequest::HttpRequest(char* input) {
	this->pinNumber = 0;
	this->pinSetting = 0;
	this->requestUrl = NULL;
	this->requestMethod = NULL;
	this->headerArray = new HttpHeaders();
	Utils* utils = new Utils();
	Tokens* headers = utils->tokeniseString(input, "\r\n");
	Serial.print("headers ");
	Serial.println(headers->count());
	for(int i=0; i<headers->count(); i++) {
		if(strncmp(headers->getToken(i), "GET", 3) == 0 || strncmp(headers->getToken(i), "POST", 4) == 0) {
			// this is the request - METHOD URL PROTOCOL
			Tokens* urlTokens = utils->tokeniseString(headers->getToken(i), " ");
			this->requestMethod = strdup(urlTokens->getToken(0));
			char* url = strdup(urlTokens->getToken(1));
			this->setRequestUrl(url);
			delete urlTokens;
		}
		else {
			if(strchr(headers->getToken(i), ':') != NULL) {
				Tokens *header = utils->tokeniseHeader(headers->getToken(i), ":");
				HttpHeader* h = new HttpHeader(header->getToken(0), header->getToken(1));
				this->headerArray->add(h);
				delete header;
			}
			else {
				Serial.println(headers->getToken(i));
			}
		}
	}

	delete headers;
	delete utils;
}

HttpRequest::~HttpRequest() {
	delete this->headerArray;
	if(this->requestMethod) free(this->requestMethod);
	if(this->requestUrl) free(this->requestUrl);
}

int HttpRequest::getPinNumber() {
	return this->pinNumber;
}

int HttpRequest::getPinSetting() {
	return this->pinSetting;
}


int HttpRequest::headerCount() {
	this->headerArray->count();
}

HttpHeader* HttpRequest::getHeader(int n) {
	//return this->headers[n];
}

HttpHeader* HttpRequest::getHeader(char* name) {
	//return this->headers[0];
}

char* HttpRequest::getRequestUrl() {
	return this->requestUrl;
}

char* HttpRequest::setRequestUrl(char* url) {
	char* retval = "200";
	this->requestUrl = url;
	char* ptr = strdup(url);
	Utils* u = new Utils();
	Tokens *t = u->tokeniseString(ptr, "/");
	if(strcmp(this->requestMethod, "POST") == 0) {
		if(t->count() >= 2) {
			if(strncmp(t->getToken(0), "gpio", 4) == 0) {
				// should be a pin number
				String s = String(t->getToken(0));
				int i = s.indexOf("gpio");
				String x = s.substring(4);
				this->pinNumber = x.toInt();
			}
			String s = String(t->getToken(1));
			this->pinSetting = s.toInt();
		}
	}
	else {
		String s = String(t->getToken(0));
		int i = s.indexOf("gpio");
		String x = s.substring(4);
		this->pinNumber = x.toInt();
	}
	free(ptr);
	delete t;
	return retval;
}

char* HttpRequest::getRequestMethod() {
	return this->requestMethod;
}
