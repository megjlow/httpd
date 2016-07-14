#ifndef keyvaluepair_h
#define keyvaluepair_h


#include <Arduino.h>


class KeyValuePair {
public:
	KeyValuePair(char* key, char* value);
	~KeyValuePair();
	char* key();
	char* value();
private:
	char* m_Key;
	char* m_Value;
};

#endif
