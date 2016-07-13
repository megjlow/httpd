#ifndef httpresponse_h
#define httpresponse_h

#include <Arduino.h>

class HttpResponse{
public:
	HttpResponse(char* code, int pinValue);
	~HttpResponse();
	char* getResponse();
private:
	char* code;
	int pinValue;
};

#endif
