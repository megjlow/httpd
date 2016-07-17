#include "HttpRequest.h"

#include "Arduino.h"
#include "HttpHeader.h"
#include "HttpHeaders.h"
#include "Tokens.h"
#include "Utils.h"
#include "RequestParams.h"
#include "FS.h"


HttpRequest::HttpRequest(char* input) {
	this->pinNumber = 0;
	this->pinSetting = 0;
	this->requestUrl = NULL;
	this->requestMethod = NULL;
	this->headerArray = new HttpHeaders();
	this->params = new RequestParams();
	Utils* utils = new Utils();
	Tokens* headers = utils->tokeniseString(input, "\r\n");
	for(int i=0; i<headers->count(); i++) {
		if(strncmp(headers->getToken(i), "GET", 3) == 0 || strncmp(headers->getToken(i), "POST", 4) == 0) {
			// this is the request - METHOD URL PROTOCOL
			Utils* u = new Utils();
			Tokens* urlTokens = u->tokeniseString(headers->getToken(i), " ");
			this->requestMethod = strdup(urlTokens->getToken(0));
			char* url = strdup(urlTokens->getToken(1));
			this->setRequestUrl(url);
			delete urlTokens;
			delete u;
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
				Tokens* t = utils->tokeniseString(headers->getToken(i), "&");
				char* filename = NULL;
				char* contents = NULL;
				for(int j=0; j<t->count(); j++) {
					Tokens* x = utils->tokeniseString(t->getToken(j), "=");
					for(int k=0; k<x->count(); k++) {
						if(strcmp(x->getToken(0), "filename") == 0) {
							filename = strdup(x->getToken(1));
						}
						if(strcmp(x->getToken(0), "contents") == 0) {
							contents = strdup(x->getToken(1));
						}
					}
					delete x;
				}
				Serial.print("filename: ");
				Serial.println(filename);
				Serial.print("contents: ");
				Serial.print(contents);
				if(filename != NULL && contents != NULL) {
					String fname = String(filename);
					fname.replace("%2F", "/");
					File f = SPIFFS.open(fname, "w");
					String s = String(contents);
					s.replace("%0A", "\n");
					s.replace("%3D", "=");
					f.print(s);
					f.close();
				}
				if(filename != NULL) {
					free(filename);
				}
				if(contents != NULL) {
					free(contents);
				}
				delete t;
			}
		}
	}

	delete headers;
	delete utils;
}

HttpRequest::~HttpRequest() {
	delete this->headerArray;
	delete this->params;
	free(this->requestMethod);
	free(this->requestUrl);
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

void HttpRequest::setRequestUrl(char* url) {
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
	delete u;
}

char* HttpRequest::getRequestMethod() {
	return this->requestMethod;
}
