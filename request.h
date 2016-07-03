#ifndef request_h
#define request_h

#include <Arduino.h>

class Header {
public:
	Header(char *header);
	~Header();
	char* key();
	char* value();
private:
	char* m_Key;
	char* m_Value;
};

class Request {
public: 
	Request(char* input);
	~Request();
	int headerCount();
	Header* getHeader(char* name);
	Header* getHeader(int n);
	char* getRequestUrl();
	char* getRequestMethod();
private:
	Header** headers;
	int nHeaders;
	char* requestMethod;
	char* requestUrl;
};

#endif