#include <Arduino.h>
#include "HttpContext.h"

#include "HttpRequest.h"
#include "HttpResponse.h"

HttpContext::HttpContext(httpd::sockets::ISocket* socket) {
	this->_socket = socket;
	this->_request = new HttpRequest(socket);
	this->_response = new HttpResponse(socket);
}

/*
HttpContext::HttpContext(WiFiClient client) {
	Serial.println(ESP.getFreeHeap());
	this->_client = client;
	this->_request = new HttpRequest(client);
	this->_response = new HttpResponse(client);
	Serial.println(ESP.getFreeHeap());
}
*/

HttpContext::~HttpContext() {
	this->_socket->flush();
	this->_socket->stop();
	delete this->_request;
	delete this->_response;
}

HttpRequest* HttpContext::request() {
	return this->_request;
}

HttpResponse* HttpContext::response() {
	return this->_response;
}
