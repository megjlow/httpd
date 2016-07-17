#ifndef requestparams_h
#define requestparams_h


#include <Arduino.h>
#include "KeyValuePair.h"


class RequestParams {
public:
	RequestParams();
	~RequestParams();
	char* getRequestParam(char* name);
private:
	KeyValuePair** params;
	int nParams;
};

#endif
