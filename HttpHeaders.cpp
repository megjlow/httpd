#include<Arduino.h>

#include "HttpHeaders.h"
#include "HttpHeader.h"
#include "Array.h"


void HttpHeaders::add(HttpHeader* header) {
	Array::add((void*)header);
}

HttpHeader* HttpHeaders::get(int n) {
	return (HttpHeader*) Array::get(n);
}

int HttpHeaders::count() {
	return Array::count();
}
