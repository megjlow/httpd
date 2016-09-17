#ifndef httpd_h
#define httpd_h

#include <Arduino.h>
#include <sockets/ISocket.h>
#include <sockets/IServerSocket.h>
#include <HttpContext.h>
#include <HttpRequest.h>
#include <HttpResponse.h>
#include <Array.h>

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
	Httpd(httpd::sockets::IServerSocket* server);
	~Httpd();
	void handleClient();
	void RegisterCallback(char* url, Callback callback);
	void RegisterCallback(char* url, Callback callback, bool wildcard);
	void begin();
	Array<CallbackFunc>* callbacks();
private:
	httpd::sockets::IServerSocket* _server;
	Array<CallbackFunc>* _callbacks;
};

#endif
