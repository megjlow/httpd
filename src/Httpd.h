#ifndef httpd_h
#define httpd_h

#include <Arduino.h>
#include <sockets/Socket.h>
#include <sockets/ServerSocket.h>
#include <sockets/WebSocketServer.h>
#include <HttpContext.h>
#include <HttpRequest.h>
#include <HttpResponse.h>
#include <Array.h>

using namespace httpd::sockets;

namespace httpd {
	typedef void (*Callback)(HttpContext*);

	class CallbackFunc {
	public:
		CallbackFunc(char* url, Callback callback, bool wildcard);
		CallbackFunc(char* url, Callback callback);
		~CallbackFunc();
		Callback getCallback();
		char* url();
		bool wildcard();
		bool isMatch(char* url);
	private:
		char* _url;
		Callback _callback;
		bool _wildcard;
	};

	class Httpd {
	public:
		Httpd(httpd::sockets::ServerSocket* server);
		~Httpd();
		void handleClient();
		void RegisterCallback(char* url, Callback callback);
		void RegisterCallback(char* url, Callback callback, bool wildcard);
		void addGlobalHeader(char* header, char* value);
		void begin();
		Array<CallbackFunc>* callbacks();
	private:
		ServerSocket* _server;
		Array<CallbackFunc>* _callbacks;
		Array<HttpHeader>* _globalHeaders;
		WebSocketServer* _socketServer;
	};

}

#endif
