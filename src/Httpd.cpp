#include <Arduino.h>
#include <sockets/Socket.h>
#include <sockets/ServerSocket.h>
#include <Hash.h>
#include <libb64/cencode.h>
#include "Httpd.h"
#include "HttpContext.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "Array.h"
#include "Utils.h"
#include "sockets/WebSocketFrame.h"
#include "sockets/WebSocket.h"
//#include "sockets/SocketContext.h"
#include "events/CallbackFunc.h"
#include "events/SocketCallbackFunc.h"
#include "Firmata.h"

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
		WebSocket* webSocket = this->_socketServer->available();
		if(_firmataConfigured) {
			while (Firmata.available()) {
				Firmata.processInput();
			}
		}
		if(webSocket != NULL) {
			unsigned long startTime = millis();
			Serial.print("WEBSOCKET START  ");
			Utils::printFreeHeap();
			Serial.println();
			if(this->_socketCallbacks->count() > 0) {
				//SocketContext* context = new SocketContext(webSocket);
				//if(context->opCode() == Opcode::close) {
				if(webSocket->opCode() == Opcode::close) {
					_socketServer->remove(webSocket);
					delete webSocket;
				}
				else {
					for(int i=0; i<this->_socketCallbacks->count(); i++) {
						SocketCallbackFunc *callback = this->_socketCallbacks->get(i);
						(*callback->getCallback())(webSocket);
					}
				}
				//delete context;
			}
			unsigned long endTime = millis();
			Serial.print("WEBSOCKET END    ");
			Utils::printFreeHeap();
			Serial.print(" ELAPSED ");
			Serial.println(endTime - startTime);
		}
		if(!socket) {
			delay(10);
			return;
		}

		Serial.print("START  ");
		Utils::printFreeHeap();
		Serial.println();
		HttpContext* context = new HttpContext(socket);
		for(int i=0; i<this->_globalHeaders->count(); i++) {
			context->response()->addHeader(new HttpHeader(this->_globalHeaders->get(i)));
		}
		if(context->request()->parseSuccess() == true) {
			// check if it's a request to upgrade to a websocket, if it is then hand it off to the websocket server
			if(context->request()->getHeader("Upgrade") != NULL && strcmp(context->request()->getHeader("Upgrade"), "websocket") == 0) {
				Serial.print("protocol "); Serial.println(context->request()->getHeader("Sec-WebSocket-Protocol"));

				char* fixedKey = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
				char* wsKey = context->request()->getHeader("Sec-WebSocket-Key");
				char appendedKey[128] = {0};
				strcat(appendedKey, wsKey);
				strcat(appendedKey, fixedKey);
				uint8_t hash[20] = {0};
				sha1(appendedKey, &hash[0]);

				int toencodelen = base64_encode_expected_len(15);
				char *encoded = new char[128];
				base64_encode_chars((char*)hash, toencodelen, encoded);

				context->response()->setResponseCode("HTTP/1.1 101 Switching Protocols");
				context->response()->addHeader("Server", "httpd");
				context->response()->addHeader("Upgrade", "websocket");
				context->response()->addHeader("Connection", "Upgrade");
				context->response()->addHeader("Sec-WebSocket-Accept", encoded);
				context->response()->addHeader("Sec-WebSocket-Protocol", "firmata");
				context->response()->addHeader("Sec-WebSocket-Version", "13");
				context->response()->sendResponse();

				//_socketServer->add(socket);
				//Firmata.setFirmwareVersion(FIRMATA_FIRMWARE_MAJOR_VERSION, FIRMATA_FIRMWARE_MINOR_VERSION);
				WebSocket* wSocket = new WebSocket(socket);

				//Firmata.attach(ANALOG_MESSAGE, analogWriteCallback);

				Firmata.begin(wSocket[0]);
				_firmataConfigured = true;
			}
			else {
				for(int i=0; i<this->_callbacks->count(); i++) {
					CallbackFunc *callback = this->_callbacks->get(i);
					if(callback->isMatch(context->request()->url(), context->request()->method())) {
						(*callback->getCallback())(context);
						break;
					}
				}
				// now we've run the callback and it has done whatever it needs to do output the result
				context->response()->sendResponse();
				// clean up
				delete socket;
				delete context;
			}
		}
		else {
			delete socket;
			delete context;
		}
		Serial.print("END    ");
		Utils::printFreeHeap();
		Serial.println();
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

	void Httpd::RegisterCallback(char* url, char* operation, void(*callback)(HttpContext* context)) {
		CallbackFunc* c = new CallbackFunc(url, operation, callback);
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




