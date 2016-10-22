#ifndef httpheader_h
#define httpheader_h

#include <Arduino.h>

class HttpHeader {
public:
	HttpHeader(char *key, char* value);
	HttpHeader(HttpHeader* header);
	~HttpHeader();
	char* key();
	char* value();
	char* toString();
private:
	char* _key;
	char* _value;
};

#endif
