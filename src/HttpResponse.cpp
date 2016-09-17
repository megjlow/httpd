#include <Arduino.h>

#include "HttpResponse.h"

HttpResponse::HttpResponse(httpd::sockets::ISocket* socket) {
	this->code = NULL;
	this->m_body = NULL;
	this->retval = NULL;
	this->_socket = socket;
	this->m_headers = new Array<HttpHeader>();
}

HttpResponse::~HttpResponse() {
	/*
	if(this->code != NULL) {
		free(this->code);
	}
	if(this->m_body != NULL) {
		free(this->m_body);
	}
	if(this->retval != NULL) {
		delete retval;
	}
	delete this->m_headers;
	*/
}

void HttpResponse::setResponseCode(char* code) {
	this->code = strdup(code);
}

void HttpResponse::addHeader(HttpHeader* header) {
	this->m_headers->add(header);
}

void HttpResponse::setBody(char* body) {
	this->m_body = strdup(body);
}

void HttpResponse::sendResponse() {
	this->_socket->print(this->code);
	this->_socket->print("\r\n");
	if(this->m_headers->count() > 0) {
		for(int i=0; i<this->m_headers->count(); i++) {
			HttpHeader* header = this->m_headers->get(i);
			this->_socket->print(header->key());
			this->_socket->print(": ");
			this->_socket->print(header->value());
		}
		this->_socket->print("\r\n");
	}
	this->_socket->print("\r\n");
	this->_socket->print(this->m_body);
	this->_socket->print("\r\n");
}

char* HttpResponse::pingResponse() {
	this->retval = new char[200];
	memset(this->retval, 0, sizeof(this->retval));
	strcat(this->retval, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nAccess-Control-Allow-Origin: *\r\n\r\n<html><head></head><body>PING</body></html>");
	return this->retval;
}

/*
void HttpResponse::sendFile(WiFiClient client, File f) {
	if(f) {
		client.print("HTTP/1.1 200 OK\r\n");
		String fname = f.name();
		if(fname.endsWith(".html") || fname.endsWith(".htm")) {
			client.print("Content-Type: text/html\r\n");
		}
		else if(fname.endsWith(".css")) {
			client.print("Content-Type: text/css\r\n");
		}
		else if(fname.endsWith(".jpg") || fname.endsWith(".jpeg")) {
			client.print("Content-Type: image/jpeg\r\n");
		}
		else if(fname.endsWith(".js")) {
			client.print("Content-Type: application/javascript\r\n");
		}
		else {
			client.print("Content-Type: application/octet-stream\r\n");
		}
		client.print("Access-Control-Allow-Origin: *\r\n\r\n");
		char outbuff[256];
		int available = 0;
		size_t read = 0;
		while((available = f.available()) > 0) {
			if(available > sizeof(outbuff)) {
				read = f.readBytes((char*)outbuff, sizeof(outbuff));
			}
			else {
				read = f.readBytes((char*)outbuff, available);
			}
			client.write((char*)outbuff, read);
		}
		f.close();
	}
}
*/
