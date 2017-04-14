#include <Arduino.h>
#include "HttpContext.h"

#include "HttpRequest.h"
#include "HttpResponse.h"

using namespace httpd::sockets;

HttpContext::HttpContext(Socket* socket) {
	this->_socket = socket;
	this->_request = new HttpRequest(socket);
	this->_response = new HttpResponse(socket);
}


HttpContext::~HttpContext() {
	if(this->_socket->isWebSocket() == 0) {
		delete this->_socket;
	}
	delete this->_request;
	delete this->_response;
}

HttpRequest* HttpContext::request() {
	return this->_request;
}

HttpResponse* HttpContext::response() {
	return this->_response;
}
