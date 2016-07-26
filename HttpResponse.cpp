#include <Arduino.h>

#include "HttpResponse.h"
#include "FS.h"
#include "ESP8266WiFi.h"

HttpResponse::HttpResponse(char* code, int pinValue) {
	this->retval = NULL;
	this->code = strdup(code);
	this->pinValue = pinValue;
}

HttpResponse::~HttpResponse() {
	free(this->code);
	if(this->retval != NULL) {
		delete retval;
	}
}

char* HttpResponse::getResponse() {
	this->retval = new char[400];
	memset(this->retval, 0, sizeof(this->retval));
	//char* retval = new char[200];
	strcat(this->retval, "HTTP/1.1 ");
	if(strcmp(this->code, "200") == 0) {
		strcat(this->retval, "200 OK\r\n");
		strcat(this->retval, "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n\r\n{\"value\":\"");
		char c[2] = {'\0','\0'};
		c[0] = this->pinValue + '0';
		strcat(this->retval, c);
		strcat(this->retval, "\"}");
	}
	else if(strcmp(this->code, "404") == 0) {
		strcat(this->retval, "404 Not Found\r\n");
		strcat(this->retval, "Content-Type: text/html\r\nAccess-Control-Allow-Origin: *\r\n\r\n");
		strcat(this->retval, "<html><head><title>Not Found</title></head><body>404 not found</body></html>");
	}
	strcat(this->retval, "\0");
	return this->retval;
}

char* HttpResponse::pingResponse() {
	this->retval = new char[200];
	strcat(this->retval, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nAccess-Control-Allow-Origin: *\r\n\r\n<html><head></head><body>PING</body></html>");
	return this->retval;
}

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

