#include "Configuration.h"
#include <Arduino.h>
#include <FS.h>
#include <Utils.h>
#include <Tokens.h>
#include <KeyValuePair.h>

Configuration::Configuration(char* fname) {
	this->settings = new KeyValuePair*[10];
	this->nSettings = 0;
	File f = SPIFFS.open("/config.txt", "r");
	if(!f) {
		Serial.print("Configuration: failed to open configuration file - ");
		Serial.println(fname);
	}
	else {
		Utils* utils = new Utils();
		char* buffer = (char*) calloc(1024, sizeof(char));
		f.readBytes(buffer, f.size());
		Tokens* lines = utils->tokeniseString(buffer, "\r\n");
		for(int i=0; i<lines->count(); i++) {
			if(strcmp(lines->getToken(i), "") != 0) {
				Tokens* setting = utils->tokeniseString(lines->getToken(i), "=");
				if(setting->count() >= 2) {
					KeyValuePair* s = new KeyValuePair(setting->getToken(0), setting->getToken(1));
					this->settings[this->nSettings] = s;
					this->nSettings++;
				}
				delete setting;
			}
		}

		delete utils;
		delete lines;
		free(buffer);
	}
}

Configuration::~Configuration() {
	for(int i=0; i<this->nSettings; i++) {
		delete this->settings[i];
	}
	delete[] this->settings;
}

char* Configuration::getConfigurationSetting(char* name) {
	char* retval = NULL;
	for(int i=0; i<this->nSettings; i++) {
		if(strcmp(this->settings[i]->key(), name) == 0) {
			retval = this->settings[i]->value();
			break;
		}
	}
	return retval;
}
