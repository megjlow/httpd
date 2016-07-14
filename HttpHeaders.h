#ifndef httpheaders_h
#define httpheaders_h

#include <Arduino.h>

#include "HttpHeader.h"
#include "Array.h"

class HttpHeaders: public Array {
public:
	void add(HttpHeader* header);
	HttpHeader* get(int i);
	int count();
};

#endif
