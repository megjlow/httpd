#ifndef response_h
#define response_h

#include <Arduino.h>

class Response{
public:
	Response(char* code, int pinValue);
	~Response();
	char* getResponse();
private:
	char* code;
	int pinValue;
};

#endif
