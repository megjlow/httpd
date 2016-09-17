#ifndef httpresponse_h
#define httpresponse_h

#include <Arduino.h>
#include <sockets/ISocket.h>
#include <HttpHeader.h>
#include <Array.h>

class HttpResponse{
public:
	HttpResponse(httpd::sockets::ISocket* socket);
	~HttpResponse();
	void setResponseCode(char* code);
	void addHeader(HttpHeader* header);
	void setBody(char* body);
	void sendResponse();
	//void sendFile(WiFiClient client, File f);
	char* pingResponse();
private:
	httpd::sockets::ISocket* _socket;
	Array<HttpHeader>* m_headers;
	char* code;
	char* m_body;
	int pinValue;
	char* retval;
};

#endif
