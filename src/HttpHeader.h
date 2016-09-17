#ifndef httpheader_h
#define httpheader_h

#include <Arduino.h>

class HttpHeader {
public:
	HttpHeader(char *key, char* value);
	~HttpHeader();
	char* key();
	char* value();
	char* toString();
private:
	char* m_Key;
	char* m_Value;
};

#endif
