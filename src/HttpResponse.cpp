#include <Arduino.h>

#include "HttpResponse.h"

HttpResponse::HttpResponse(httpd::sockets::Socket* socket) {
	this->_code = NULL;
	this->_body = NULL;
	this->retval = NULL;
	this->_socket = socket;
	this->_headers = new Array<HttpHeader>();
}

HttpResponse::~HttpResponse() {
	if(this->_code != NULL) {
		free(this->_code);
	}
	if(this->_body != NULL) {
		free(this->_body);
	}
	if(this->retval != NULL) {
		delete retval;
	}
	delete this->_headers;
}

void HttpResponse::setResponseCode(char* code) {
	this->_code = strdup(code);
}

void HttpResponse::addHeader(HttpHeader* header) {
	this->_headers->add(header);
}

void HttpResponse::addHeader(char* key, char* value) {
	HttpHeader *header = new HttpHeader(key, value);
	this->_headers->add(header);
}

void HttpResponse::setBody(char* body) {
	this->_body = strdup(body);
}

void HttpResponse::setBody(String body) {
	this->_body = (char*) calloc(body.length() + 1, sizeof(char));
	body.toCharArray(this->_body, body.length() + 1);
}

void HttpResponse::sendResponse() {
	if(this->_code != NULL) {
		char* outBuf = new char[1024];
		memset(outBuf, '\0', sizeof(outBuf));
		strcat(outBuf, this->_code);
		strcat(outBuf, "\r\n");
		for(int i=0; i<this->_headers->count(); i++) {
			HttpHeader* header = this->_headers->get(i);
			strcat(outBuf, header->key());
			strcat(outBuf, ": ");
			strcat(outBuf, header->value());
			strcat(outBuf, "\r\n");
		}
		if(this->_body != NULL) {
			strcat(outBuf, "\r\n");
			strcat(outBuf, this->_body);
		}
		strcat(outBuf, "\r\n");
		Serial.println(outBuf);
		this->_socket->write((uint8_t*)outBuf, strlen(outBuf));
		delete outBuf;
	}
}

char* HttpResponse::pingResponse() {
	this->retval = new char[200];
	memset(this->retval, 0, sizeof(this->retval));
	strcat(this->retval, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nAccess-Control-Allow-Origin: *\r\n\r\n<html><head></head><body>PING</body></html>");
	return this->retval;
}


void HttpResponse::sendFile(File f) {
	if(f) {
		this->_socket->print("HTTP/1.1 200 OK\r\n");
		String fname = f.name();
		if(fname.endsWith(".html") || fname.endsWith(".htm")) {
			this->_socket->print("Content-Type: text/html\r\n");
		}
		else if(fname.endsWith(".css")) {
			this->_socket->print("Content-Type: text/css\r\n");
		}
		else if(fname.endsWith(".jpg") || fname.endsWith(".jpeg")) {
			this->_socket->print("Content-Type: image/jpeg\r\n");
		}
		else if(fname.endsWith(".js")) {
			this->_socket->print("Content-Type: application/javascript\r\n");
		}
		else {
			this->_socket->print("Content-Type: application/octet-stream\r\n");
		}
		this->_socket->print("Access-Control-Allow-Origin: *\r\n\r\n");
		char outbuff[512];
		int available = 0;
		size_t read = 0;
		while((available = f.available()) > 0) {
			if(available > sizeof(outbuff)) {
				read = f.readBytes((char*)outbuff, sizeof(outbuff));
			}
			else {
				read = f.readBytes((char*)outbuff, available);
			}
			this->_socket->write((uint8_t*)outbuff, read);
			delay(1);
		}
		f.close();
	}
}



