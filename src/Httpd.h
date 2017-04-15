#ifndef httpd_h
#define httpd_h

#include <Arduino.h>
#include <sockets/Socket.h>
#include <sockets/ServerSocket.h>
#include <sockets/WebSocketServer.h>
#include <events/CallbackFunc.h>
#include <events/SocketCallbackFunc.h>
#include <SocketContext.h>
#include <HttpContext.h>
#include <HttpRequest.h>
#include <HttpResponse.h>
#include <Array.h>

using namespace httpd::sockets;
using namespace httpd::events;

namespace httpd {

	class Httpd {
	public:
		Httpd(httpd::sockets::ServerSocket* server);
		~Httpd();
		void handleClient();
		void RegisterCallback(char* url, Callback callback);
		void RegisterCallback(char* url, Callback callback, bool wildcard);
		void RegisterSocketCallback(SocketCallback callback);
		void addGlobalHeader(char* header, char* value);
		void begin();
		Array<CallbackFunc>* callbacks();
	private:
		ServerSocket* _server;
		Array<CallbackFunc>* _callbacks;
		Array<SocketCallbackFunc>* _socketCallbacks;
		Array<HttpHeader>* _globalHeaders;
		WebSocketServer* _socketServer;
	};

}

#endif
