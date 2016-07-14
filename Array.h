#ifndef array_h
#define array_h


#include <Arduino.h>


class Array {
public:
	Array();
	~Array();
	void add(void* element);
	void* get(int n);
	int count();
private:
	int nElements;
	void** elementArray;
};

#endif
