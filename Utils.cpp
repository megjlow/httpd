#include <Arduino.h>
#include "Utils.h"


Utils::Utils() {

}

Utils::~Utils() {

}

Tokens* Utils::tokeniseString(char* input, char* delim) {
	Tokens* retval = new Tokens();
	char* token = NULL;
	char* c;

	token = strtok_r(input, delim, &c);
	while(token != NULL) {
		retval->addToken(token);
		token = strtok_r(NULL, delim, &c);
	}
	return retval;
}

Tokens* Utils::tokeniseHeader(char* header, char* delim) {
	Tokens* retval = new Tokens();

	char* token = NULL;
	char* c;
	token = strtok_r(header, delim, &c);
	retval ->addToken(token);
	retval->addToken(c);

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
