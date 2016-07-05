#ifndef request_h
#define request_h

#include <Arduino.h>

class Header {
public:
	Header(char *key, char* value);
	~Header();
	char* key();
	char* value();
	char* toString();
private:
	char* m_Key;
	char* m_Value;
};

class Headers {
public:
	Headers();
	~Headers();
	void addHeader(Header* header);
	Header* getHeader(int i);
	int count();
private:
	Header** headerArray;
	int nHeaders;
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
	void parseUrl();
	int getPinNumber();
	int getPinSetting();
private:
	Headers* headerArray;
	int nHeaders;
	char* requestMethod;
	char* requestUrl;
	int pinNumber;
	int pinSetting;
	char* setRequestUrl(char* url);
};

#endif
