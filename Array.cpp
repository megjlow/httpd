#include "Array.h"
#include <Arduino.h>

#include <HttpHeader.h>


/*
Only for elements which can be deleted i.e. must have been created with a new call.
 */
Array::Array() {
	this->nElements = 0;
	this->elementArray = new void*[30];
}

Array::~Array() {
	for(int i=0; i<this->nElements; i++) {
		delete this->elementArray[i];
	}
	delete[] this->elementArray;
}

void Array::add(void* element) {
	this->elementArray[this->nElements] = element;
	this->nElements++;
}

void* Array::get(int n) {
	void* retval = NULL;
	if(n <= this->nElements) {
		return this->elementArray[n];
	}
	return retval;
}

int Array::count() {
	return this->nElements;
}
