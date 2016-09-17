#include <Arduino.h>
#include <sockets/ISocket.h>
#include <sockets/IServerSocket.h>
#include "Httpd.h"
#include "HttpContext.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "Array.h"


CallbackFunc::CallbackFunc(char* url, Callback callback, bool wildcard) {
	this->_url = strdup(url);
	this->_callback = callback;
	this->_wildcard = wildcard;
}

CallbackFunc::CallbackFunc(char* url, Callback callback): CallbackFunc(url, callback, false) {
}
CallbackFunc::~CallbackFunc() {
	free(this->_url);
}
Callback CallbackFunc::getCallback() {
	return this->_callback;
}
char* CallbackFunc::url() {
	return this->_url;
}

bool CallbackFunc::wildcard() {
	return this->_wildcard;
}

bool CallbackFunc::isMatch(char* url) {
	bool retval = false;
	if(this->_wildcard && strncmp(this->_url, url, strlen(this->_url)) == 0) {
		retval = true;
	}
	else if(strcmp(this->_url, url) == 0) {
		retval = true;
	}
	return retval;
}


Httpd::Httpd(httpd::sockets::IServerSocket* server) {
	this->_callbacks = new Array<CallbackFunc>();
	this->_server = server;
}

Httpd::~Httpd() {
	delete this->_callbacks;
}

void Httpd::begin() {
	this->_server->begin();
}

void Httpd::handleClient() {
	httpd::sockets::ISocket* socket = this->_server->available();
	if(!socket) {
		return;
	}
	Serial.println("got client");
	HttpContext* context = new HttpContext(socket);
	if(context->request()->parseSuccess() == true) {
		for(int i=0; i<this->_callbacks->count(); i++) {
			CallbackFunc *callback = this->_callbacks->get(i);
			callback->isMatch(context->request()->url());
			if(callback->isMatch(context->request()->url())) {
				Serial.println("matched callback");
				(*callback->getCallback())(context);
			}
		}

	// now we've run the callback and it has done whatever it needs to do output the result
	context->response()->sendResponse();
	}
	delete context;
}

Array<CallbackFunc>* Httpd::callbacks() {
	return this->_callbacks;
}

void Httpd::RegisterCallback(char* url, void(*callback)(HttpContext* context), bool wildcard) {
	CallbackFunc* c = new CallbackFunc(url, callback, wildcard);
	this->_callbacks->add(c);
}

void Httpd::RegisterCallback(char* url, void(*callback)(HttpContext* context)) {
	this->RegisterCallback(url, callback, false);
}



