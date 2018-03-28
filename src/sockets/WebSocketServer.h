#ifndef websocketserver_h
#define websocketserver_h

#include <Array.h>
#include <sockets/Socket.h>
#include <sockets/WebSocket.h>
#include <HttpContext.h>

using namespace httpd::sockets;

class WebSocketServer {
public:
	WebSocketServer();
	~WebSocketServer();
	void add(HttpContext* context, Socket* socket);
	WebSocket* available();
private:
	Array<WebSocket>* _sockets;
};

#endif
