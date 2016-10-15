#include <Arduino.h>
#include <sockets/WebSocketServer.h>
#include <sockets/Socket.h>
#include <Hash.h>
#include <libb64/cencode.h>

using namespace httpd::sockets;

WebSocketServer::WebSocketServer() {

}

WebSocketServer::~WebSocketServer() {

}

void WebSocketServer::add(HttpContext* context, Socket* socket) {
	Serial.println("add");
	socket->setWebSocket();
	if(socket->connected()) {
		Serial.println("socket still connected");
	}
	char* fixedKey = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
  char* wsKey = context->request()->getHeader("Sec-WebSocket-Key");
  char appendedKey[128];
  strcat(appendedKey, wsKey);
  strcat(appendedKey, fixedKey);
  uint8_t hash[20];
  sha1(appendedKey, &hash[0]);
  char toencodeLen = strlen((char*) hash) + 1;
  char *encoded = new char[base64_encode_expected_len(toencodeLen)+1];
  base64_encode_chars((char*)hash, toencodeLen, encoded);

  context->response()->setResponseCode("HTTP/1.1 101 Switching Protocols");
  context->response()->addHeader("Upgrade", "websocket");
  context->response()->addHeader("Connection", "Upgrade");
  context->response()->addHeader("Sec-WebSocket-Accept", encoded);
  context->response()->addHeader("Sec-WebSocket-Protocol:", "arduino");
  context->response()->addHeader("Sec-WebSocket-Version", "13");
  context->response()->addHeader("Access-Control-Allow-Origin", "*");
  context->response()->sendResponse();

  delete context;

}
