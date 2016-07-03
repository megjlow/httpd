#include "Arduino.h"
#include "httpd.h"
#include "request.h"
#include "response.h"


Httpd::Httpd() {;
}

Httpd::~Httpd() {

}

Request* Httpd::parseRequest(char* input){
	Request* retval = new Request(input);
	return retval;
}

Response* Httpd::createResponse(char* code, int pinValue) {
	Response* retval = new Response(code, pinValue);
	return retval;
}



