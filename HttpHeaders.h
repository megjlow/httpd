#ifndef httpheaders_h
#define httpheaders_h

#include <Arduino.h>

#include "HttpHeader.h"

class HttpHeaders {
public:
	HttpHeaders();
	~HttpHeaders();
	void addHeader(HttpHeader* header);
	HttpHeader* getHeader(int i);
	int count();
private:
	HttpHeader** headerArray;
	int nHeaders;
};

#endif
