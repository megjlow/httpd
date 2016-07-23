#ifndef requestparams_h
#define requestparams_h


#include <Arduino.h>
#include "KeyValuePair.h"


class RequestParameters {
public:
	RequestParameters();
	~RequestParameters();
	char* getRequestParameter(char* name);
	void addRequestParameter(char* param);
private:
	KeyValuePair** params;
	int nParams;
};

#endif
