#ifndef config_h
#define config_h

#include <Arduino.h>
#include "KeyValuePair.h"
#include "Array.h"


class Configuration: public Array {
public:
	Configuration(char* fname);
	char* getConfigurationSetting(char* name);
};

#endif
