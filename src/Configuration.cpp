#include "Configuration.h"
#include <Arduino.h>
#include <Utils.h>
#include <KeyValuePair.h>
#include <FS.h>

Configuration::Configuration(char* fname) {
	this->_settings = new Array<KeyValuePair>();
	File f = SPIFFS.open("/config.txt", "r");
	if(!f) {
		Serial.print("Configuration: failed to open configuration file - ");
		Serial.println(fname);
	}
	else {
		char* buffer = (char*) calloc(1024, sizeof(char));
		f.readBytes(buffer, f.size());
		Array<char>* lines = Utils::tokeniseString(buffer, "\r\n");
		for(int i=0; i<lines->count(); i++) {
			if(strcmp(lines->get(i), "") != 0) {
				Array<char>* setting = Utils::tokeniseString(lines->get(i), "=");
				if(setting->count() >= 2) {
					KeyValuePair* s = new KeyValuePair(setting->get(0), setting->get(1));
					this->_settings->add(s);
				}
				delete setting;
			}
		}

		delete lines;
		free(buffer);
	}
}

Configuration::~Configuration() {
	delete this->_settings;
}

int Configuration::countSettings() {
	return this->_settings->count();
}

char* Configuration::get(char* name) {
	char* retval = NULL;
	for(int i=0; i<this->_settings->count(); i++) {
		if(strcmp(this->_settings->get(i)->key(), name) == 0) {
			retval = this->_settings->get(i)->value();
			break;
		}
	}
	return retval;
}
