#include <Arduino.h>
#include <sockets/WebSocketServer.h>
#include <sockets/Socket.h>
#include <Hash.h>
#include <libb64/cencode.h>

using namespace httpd::sockets;

WebSocketServer::WebSocketServer() {
	this->_sockets = new Array<Socket>();
}

WebSocketServer::~WebSocketServer() {

}

Socket* WebSocketServer::available() {
	Socket* retval = NULL;
	if(this->_sockets->count() > 0)
	{
		for(int i=0; i<_sockets->count(); i++)
		{
			if(_sockets->get(i)->available() > 0) {
				retval = _sockets->get(i);
			}
		}
	}
	return retval;
}

void WebSocketServer::add(HttpContext* context, Socket* socket) {
	socket->setNoDelay(true);
	socket->setWebSocket();
	this->_sockets->add(socket);
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
    context->response()->addHeader("Sec-WebSocket-Protocol", "arduino");
    context->response()->addHeader("Sec-WebSocket-Version", "13");
    context->response()->sendResponse();

    delete encoded;

}
