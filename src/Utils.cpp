#include <Arduino.h>
#include "Utils.h"
#include "Array.h"


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
