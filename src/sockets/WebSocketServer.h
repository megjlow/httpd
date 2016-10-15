#ifndef websocketserver_h
#define websocketserver_h

#include <Array.h>
#include <sockets/Socket.h>
#include <HttpContext.h>

using namespace httpd::sockets;

class WebSocketServer {
public:
	WebSocketServer();
	~WebSocketServer();
	void add(HttpContext* context, Socket* socket);
private:
	Array<Socket>* _sockets;
};

#endif
