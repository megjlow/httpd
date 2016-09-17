#ifndef config_h
#define config_h

#include <Arduino.h>
#include "KeyValuePair.h"


class Configuration {
public:
	Configuration(char* fname);
	~Configuration();
	char* getConfigurationSetting(char* name);
private:
	KeyValuePair** settings;
	int nSettings;
};

#endif
