#include <Arduino.h>
#include "HttpContext.h"

#include "HttpRequest.h"
#include "HttpResponse.h"

HttpContext::HttpContext(httpd::sockets::Socket* socket) {
	this->_socket = socket;
	this->_request = new HttpRequest(socket);
	this->_response = new HttpResponse(socket);
}


HttpContext::~HttpContext() {
	this->_socket->flush();
	this->_socket->stop();
	delete this->_socket;
	delete this->_request;
	delete this->_response;
}

HttpRequest* HttpContext::request() {
	return this->_request;
}

HttpResponse* HttpContext::response() {
	return this->_response;
}
