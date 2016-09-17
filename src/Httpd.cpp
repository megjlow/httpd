#include <Arduino.h>
#include <sockets/ISocket.h>
#include <sockets/IServerSocket.h>
#include "Httpd.h"
#include "HttpContext.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "Array.h"


Httpd::Httpd(httpd::sockets::IServerSocket* server) {
	this->_callbacks = new Array<CallbackFunc>();
	this->_server = server;
}

/*
Httpd::Httpd(WiFiServer* server) {
	this->_callbacks = new Array<CallbackFunc>();
	this->_server = server;
}
*/

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
	HttpContext* context = new HttpContext(socket);
	if(context->request()->parseSuccess() == true) {
		for(int i=0; i<this->_callbacks->count(); i++) {
			if(strcmp(this->_callbacks->get(i)->url(), context->request()->url()) == 0) {
				// found a registered callback for the request url, call it
				CallbackFunc *callback = this->_callbacks->get(i);
				(*callback->getCallback())(context);
			}
		}

	// now we've run the callback and it has done whatever it needs to do output the result
	context->response()->sendResponse();
	}
	delete context;
	/*
	WiFiClient client = this->_server->available();
	//Client* client = dynamic_cast<Client*>(&c);
	if (!client) {
	  return;
	}
	HttpContext* context = new HttpContext(client);
	if(context->request()->parseSuccess() == true) {
	for(int i=0; i<this->_callbacks->count(); i++) {
		if(strcmp(this->_callbacks->get(i)->url(), context->request()->url()) == 0) {
			// found a registered callback for the request url, call it
			CallbackFunc *callback = this->_callbacks->get(i);
			(*callback->getCallback())(context);
		}
	}
	// now we've run the callback and it has done whatever it needs to do output the result
	context->response()->sendResponse();
	}
	delete context;
	*/
}

/*
HttpContext* Httpd::ProcessRequest(WiFiClient client) {
	HttpContext* retval = new HttpContext(client);
	// check for a registered callback for the request url
	for(int i=0; i<this->_callbacks->count(); i++) {
		if(strcmp(this->_callbacks->get(i)->url(), retval->request()->url()) == 0) {
			// found a registered callback for the request url, call it
			CallbackFunc *callback = this->_callbacks->get(i);
			(*callback->getCallback())(retval);
		}
	}
	return retval;
}
*/

void Httpd::sendResponse(HttpResponse* response) {

}

Array<CallbackFunc>* Httpd::callbacks() {
	return this->_callbacks;
}

void Httpd::RegisterCallback(char* url, void(*callback)(HttpContext* context)) {
	CallbackFunc* c = new CallbackFunc(url, callback);
	this->_callbacks->add(c);
}



