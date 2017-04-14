#include <Arduino.h>
#include <sockets/Socket.h>
#include <sockets/ServerSocket.h>
#include "Httpd.h"
#include "HttpContext.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "Array.h"
#include "Utils.h"
#include "sockets/WebSocketFrame.h"
#include "SocketContext.h"

using namespace httpd::sockets;

namespace httpd {


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
		Socket* webSocket = this->_socketServer->available();
		if(webSocket != NULL) {
			SocketContext* context = new SocketContext(webSocket);
			Serial.print("got message: ["); Serial.println(context->getMessage()); Serial.print("]");
			context->sendMessage("bum");
		}
		if(!socket) {
			delay(1000);
			return;
		}

		//this->_webSockets->add(socket);
		Serial.print("START  ");
		Utils::printFreeHeap();
		HttpContext* context = new HttpContext(socket);
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
		Serial.print("END    ");
		Utils::printFreeHeap();
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

}




