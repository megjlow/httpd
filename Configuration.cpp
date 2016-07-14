#include "Configuration.h"
#include <Arduino.h>
#include <FS.h>
#include <Utils.h>
#include <Tokens.h>
#include <KeyValuePair.h>
#include <Array.h>

Configuration::Configuration(char* fname): Array() {
	File f = SPIFFS.open("/config.txt", "r");
	if(!f) {
		Serial.print("Configuration: failed to open configuration file - ");
		Serial.println(fname);
	}
	else {
		Utils* utils = new Utils();
		char* buffer = (char*) calloc(2048, sizeof(char));
		f.readBytes(buffer, f.size());
		Tokens* lines = utils->tokeniseString(buffer, "\r\n");
		for(int i=0; i<lines->count(); i++) {
			if(strcmp(lines->getToken(i), "") != 0) {
				Tokens* setting = utils->tokeniseString(lines->getToken(i), "=");
				if(setting->count() >= 2) {
					KeyValuePair* s = new KeyValuePair(setting->getToken(0), setting->getToken(1));
					Array::add((void*)s);
				}
				delete setting;
			}
		}

		delete utils;
		delete lines;
		free(buffer);
	}
}


char* Configuration::getConfigurationSetting(char* name) {
	char* retval = NULL;
	for(int i=0; i<Array::count(); i++) {
		KeyValuePair* pair = (KeyValuePair*) Array::get(i);
		if(strcmp(pair->key(), name) == 0) {
			retval = pair->value();
			break;
		}
	}
	return retval;
}
