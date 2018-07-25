#include <Arduino.h>
#include <sockets/Frame.h>


Frame::Frame(uint8_t* data, int length) {
	_data = data;
	_length = length;
}

Frame::~Frame() {
	if(_data != NULL) {
		delete _data;
	}
}

int Frame::length() {
	return _length;
}

uint8_t* Frame::data() {
	return _data;
}

void Frame::dump() {
	Serial.print("<Frame>");
	for(int i=0; i<_length; i++) {
		Serial.print(_data[i], HEX); Serial.print(" ");
	}
	Serial.println("</Frame>");
}


