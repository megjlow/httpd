#include <Arduino.h>
#include <sockets/WebSocketServer.h>
#include <sockets/Socket.h>
#include <sockets/WebSocket.h>


using namespace httpd::sockets;

WebSocketServer::WebSocketServer() {
	this->_sockets = new Array<WebSocket>();
}

WebSocketServer::~WebSocketServer() {

}

WebSocket* WebSocketServer::available() {
	WebSocket* retval = NULL;
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

void WebSocketServer::add(Socket* socket) {
	_sockets->add(new WebSocket(socket));
}

void WebSocketServer::remove(WebSocket* socket) {
	_sockets->remove(socket);
}


