#include <Arduino.h>
#include "Utils.h"
#include "Array.h"

#ifdef ARDUINO_STM32_FEATHER
#include <adafruit_feather.h>
#endif


Utils::Utils() {

}

Utils::~Utils() {

}


char* Utils::strdup(char* input) {
	char* retval = new char[strlen(input) + 1];
	strcpy(retval, input);
	retval[strlen(input) + 1] = '\0';
	return retval;
}

Array<char>* Utils::tokeniseString(char* input, char* delim) {
	Array<char>* retval = new Array<char>();
	char* token = NULL;
	char* c;

	token = strtok_r(input, delim, &c);
	while(token != NULL) {
		retval->add(token);
		token = strtok_r(NULL, delim, &c);
	}
	return retval;
}

Array<char>* Utils::tokeniseHeader(char* header, char* delim) {
	Array<char>* retval = new Array<char>();

	char* token = NULL;
	char* c;
	token = strtok_r(header, delim, &c);
	retval->add(token);
	retval->add(c);

	return retval;
}

void Utils::urlEncode(char* dst, const char* src){
    char s;
    while((s = *src++)){
        if(s <= ',' || s == '/' ||
                (s >= ':' && s <= '@') ||
                s == '[' || s == ']' ||
                s >= 0x7F){
            char a = s >> 4, b = s & 0xF;
            if(a >= 10)
                a += 'A' - 10;
            else
                a += '0';
            if(b >= 10)
                b += 'A' - 10;
            else
                b += '0';
            dst[0] = '%';
            dst[1] = a;
            dst[2] = b;
            dst += 3;
        } else
            *dst++ = s;
    }
    *dst = '\0';
}

void Utils::urlDecode(char *dst, const char *src) {
  char a, b,c;
  if (dst==NULL) return;
  while (*src) {
    if ((*src == '%') &&
      ((a = src[1]) && (b = src[2])) &&
      (isxdigit(a) && isxdigit(b))) {
      if (a >= 'a')
        a -= 'a'-'A';
      if (a >= 'A')
        a -= ('A' - 10);
      else
        a -= '0';
      if (b >= 'a')
        b -= 'a'-'A';
      if (b >= 'A')
        b -= ('A' - 10);
      else
        b -= '0';
      *dst++ = 16*a+b;
      src+=3;
    }
    else {
        c = *src++;
        if(c=='+')c=' ';
      *dst++ = c;
    }
  }
  *dst++ = '\0';
}

void Utils::printFreeHeap() {
#ifdef ARDUINO_STM32_FEATHER
	Serial.print(Feather.dbgHeapFree());
#elif ESP8266
	Serial.print(ESP.getFreeHeap());
#endif
}


typedef enum {
	continuation = 0x00,
	text = 0x01,
	binary = 0x02,
	close = 0x08,
	ping = 0x09,
	pong = 0x0A
} Opcode;

void Utils::dumpWsMessage(char* message) {
	uint8_t _fin = ((*message >> 7) & 0x01); // this had best be 0x01 text message
	uint8_t _rsv1 = ((*message >> 6) & 0x01);
	uint8_t _rsv2 = ((*message >> 5) & 0x01);
	uint8_t _rsv3 = ((*message >> 4) & 0x01);
	uint8_t _opcode = (Opcode) (*message & 0x0F);
	message++;
	uint8_t _masked = ((*message >> 7) & 0x01);
	uint8_t _length = (*message & 0x7F);
	message++;
	if(_length == 126) {
		// next two bytes contain the actual length of the message
		_length = message[0] << 8 | message[1];
		message += 2;
	}
	if(_length == 127) {
		// next eight bytes contain the actual length of the message
		// at this point we should probably just explode
		_length = message[4] << 24 | message[5] << 16 | message[6] << 8 | message[7];
		message += 8;
	}

	/*
	char* body = message;
	_body = new char[_length + 1];
	for(int i=0; i<_length; i++) {
		_body[i] = body[i];
	}
	_body[_length] = 0;
	*/
	Serial.print("fin: ");Serial.println(_fin);
	Serial.print("rsv1: ");Serial.println(_rsv1);
	Serial.print("rsv2: "); Serial.println(_rsv2);
	Serial.print("rsv3: "); Serial.println(_rsv3);
	Serial.print("opcode: "); Serial.println(_opcode);
	Serial.print("masked: "); Serial.println(_masked);
	Serial.print("length: "); Serial.println(_length);
	//Serial.print("mask: [");for(int i=0; i<4; i++) { Serial.print(_mask[i], HEX); Serial.print(" "); } Serial.println("]");
	//Serial.print("decoded: ["); Serial.print(_body);Serial.println("]");
}
