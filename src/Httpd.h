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
	//CallbackFunc(char* url, void(*callback)(HttpContext* context)) {
	CallbackFunc(char* url, Callback callback) {
		this->_url = strdup(url);
		this->_callback = callback;
	}
	~CallbackFunc() {
		free(this->_url);
	}
	Callback getCallback() {
		return this->_callback;
	}
	char* url() {
		return this->_url;
	}
private:
	char* _url;
	Callback _callback;
	//void (*m_callback)(HttpContext* context);
	//void *(*c)() m_func;
};

class Httpd {
public:
	Httpd(httpd::sockets::IServerSocket* server);
	//Httpd(WiFiServer* server);
	~Httpd();
	void handleClient();
	void sendResponse(HttpResponse* response);
	//HttpContext* ProcessRequest(WiFiClient client);
	void RegisterCallback(char* url, Callback callbak);
	void begin();
	Array<CallbackFunc>* callbacks();
private:
	//WiFiServer* _server;
	httpd::sockets::IServerSocket* _server;
	Array<CallbackFunc>* _callbacks;
};

#endif
