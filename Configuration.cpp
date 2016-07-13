#include "Configuration.h"
#include <Arduino.h>
#include <FS.h>

Configuration::Configuration(char* fname) {
	File f = SPIFFS.open("/config.txt", "r");
	if(!f) {
		Serial.print("Configuration: failed to open configuration file - ");
		Serial.println(fname);
	}
	else {
		/*
		char* buffer = (char*) calloc(1024, sizeof(char));
		f.readBytes(buffer, f.size());
		Serial.println(buffer);
		free(buffer);
		*/
	}
}

Configuration::~Configuration() {

}
