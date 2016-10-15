#ifndef config_h
#define config_h

#include <Arduino.h>
#include <KeyValuePair.h>
#include <Array.h>

class Configuration {
public:
	Configuration(char* fname);
	~Configuration();
	char* get(char* name);
	int countSettings();
private:
	Array<KeyValuePair>* _settings;
};

#endif
