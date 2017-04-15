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
#include "events/CallbackFunc.h"
#include "events/SocketCallbackFunc.h"

using namespace httpd::sockets;
using namespace httpd::events;

namespace httpd {


	Httpd::Httpd(ServerSocket* server) {
		this->_callbacks = new Array<CallbackFunc>();
		this->_socketCallbacks = new Array<SocketCallbackFunc>();
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
			if(this->_socketCallbacks->count() > 0) {
				SocketContext* context = new SocketContext(webSocket);
				for(int i=0; i<this->_socketCallbacks->count(); i++) {
					SocketCallbackFunc *callback = this->_socketCallbacks->get(i);
					(*callback->getCallback())(context);
				}
			}
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

	void Httpd::RegisterSocketCallback(SocketCallback callback)
	{
		SocketCallbackFunc* f = new SocketCallbackFunc(callback);
		this->_socketCallbacks->add(f);
	}

}




