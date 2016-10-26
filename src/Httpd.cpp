#include <Arduino.h>
#include <sockets/Socket.h>
#include <sockets/ServerSocket.h>
#include "Httpd.h"
#include "HttpContext.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "Array.h"
#include "Utils.h"

using namespace httpd::sockets;


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
	//int strncmp(const char *s1, const char *s2, size_t n);
	else if(strncmp(this->_url, url, sizeof(this->_url)) == 0) {
	//else if(strcmp(this->_url, url) == 0) {
		retval = true;
	}
	return retval;
}


Httpd::Httpd(ServerSocket* server) {
	this->_callbacks = new Array<CallbackFunc>();
	this->_server = server;
	this->_globalHeaders = new Array<HttpHeader>();
	this->_webSockets = new Array<Socket>();
	this->_socketServer = new WebSocketServer();
}

Httpd::~Httpd() {
	delete this->_callbacks;
}

void Httpd::begin() {
	this->_server->begin();
}

void Httpd::handleClient() {
	Socket* socket = this->_server->available();
	if(!socket) {
		delay(10);
		return;
	}
	//this->_webSockets->add(socket);
	int startTime = millis();
	Serial.print("START  ");
	Utils::printFreeHeap(); Serial.println();
	HttpContext* context = new HttpContext(socket);
	socket->setNoDelay(false);
	for(int i=0; i<this->_globalHeaders->count(); i++) {
		context->response()->addHeader(new HttpHeader(this->_globalHeaders->get(i)));
	}
	if(context->request()->parseSuccess() == true) {
		// check if it's a request to upgrade to a websocket, if it is then hand it off to the websocket server
		if(context->request()->getHeader("Upgrade") != NULL && strcmp(context->request()->getHeader("Upgrade"), "websocket") == 0) {
			this->_socketServer->add(context, socket);
		}
		else {
			for(int i=0; i<this->_callbacks->count(); i++) {
				CallbackFunc *callback = this->_callbacks->get(i);
				callback->isMatch(context->request()->url());
				if(callback->isMatch(context->request()->url())) {
					(*callback->getCallback())(context);
					break;
				}
			}
			// now we've run the callback and it has done whatever it needs to do output the result
			context->response()->sendResponse();
		}
	}
	delete context;

	int endTime = millis();
	Serial.print("END    ");
	Utils::printFreeHeap();
	Serial.print(" elapsed: "); Serial.print(endTime - startTime); Serial.println("");

}

Array<CallbackFunc>* Httpd::callbacks() {
	return this->_callbacks;
}

void Httpd::addGlobalHeader(char* header, char* value) {
	this->_globalHeaders->add(new HttpHeader(header, value));
}

void Httpd::RegisterCallback(char* url, void(*callback)(HttpContext* context), bool wildcard) {
	CallbackFunc* c = new CallbackFunc(url, callback, wildcard);
	this->_callbacks->add(c);
}

void Httpd::RegisterCallback(char* url, void(*callback)(HttpContext* context)) {
	this->RegisterCallback(url, callback, false);
}




