#ifndef array_h
#define array_h

#include "KeyValuePair.h"

template <typename T> class Array {
public:
	Array(): Array(10){
	}
	Array(int initialSize) {
		this->m_Array = new T*[initialSize];
		this->m_Size = initialSize;
		this->m_Count = 0;
	}
	~Array() {
		for(int i=0; i<this->m_Count; i++) {
			delete this->m_Array[i];
		}
		delete[] this->m_Array;
	}
	void add(T* element);
	T* get(int idx);
	int count();
private:
	int m_Size; // size of array
	int m_Count;// number of elements in array
	T** m_Array;// the array
};

template <typename T>
void Array<T>::add(T* element) {
	if(this->m_Count >= this->m_Size) {
		// resize the array, assign a new bigger array and copy the elements into it
		T** newArray = new T*[this->m_Size + 10];
		this->m_Size = this->m_Size + 10;
		for(int i=0; i<m_Count; i++) {
			newArray[i] = this->m_Array[i];
			this->m_Array[i] = NULL;
		}
		delete this->m_Array;
		this->m_Array = newArray;
	}
	this->m_Array[m_Count] = element;
	this->m_Count++;
}

template <typename T>
T* Array<T>::get(int idx) {
	T* retval = NULL;
	if(idx <= this->m_Count) {
		retval = this->m_Array[idx];
	}
	return retval;
}

template <typename T>
int Array<T>::count() {
	return this->m_Count;
}

template <>
class Array<KeyValuePair> {
public:
	Array(): Array(10) {
	}
	Array(int initialSize) {
		this->_array = new KeyValuePair*[initialSize];
		this->_size = 10;
		this->_count = 0;
	}
	~Array() {
		for(int i=0; i<this->_count; i++) {
			delete this->_array[i];
		}
		delete[] this->_array;
	}
	void add(KeyValuePair* kvp) {
		if(this->_count >= this->_size) {
			// resize the array, assign a new bigger array and copy the elements into it
			KeyValuePair** newArray = new KeyValuePair*[this->_size + 10];
			this->_size = this->_size + 10;
			for(int i=0; i<_count; i++) {
				newArray[i] = this->_array[i];
				this->_array[i] = NULL;
			}
			delete this->_array;
			this->_array = newArray;
		}
		this->_array[_count] = kvp;
		this->_count++;
	}
	KeyValuePair* get(char* key) {
		KeyValuePair* retval = NULL;
		for(int i=0; i<_count; i++) {
			if(strcmp(_array[i]->key(), key) == 0) {
				retval = _array[i];
				break;
			}
		}
		return retval;
	}
	KeyValuePair* get(int idx) {
		KeyValuePair* retval = NULL;
		if(idx <= this->_count) {
			retval = this->_array[idx];
		}
		return retval;
	}
	int size() {
		return this->_size;
	}
	int count() {
		return this->_count;
	}
private:
	KeyValuePair** _array;
	int _size;
	int _count;
};


template <>
class Array<char> {
public:
	Array(): Array(10) {
	}
	Array(int initialSize) {
		this->_array = new char*[initialSize];
		this->_size = initialSize;
		this->_count = 0;
	}
	~Array() {
		for(int i=0; i<this->_count; i++) {
			free(this->_array[i]);
		}
		delete[] this->_array;
	}
	void add(char* element) {
		if(this->_count >= this->_size) {
			// resize the array, assign a new bigger array and copy the elements into it
			char** newArray = new char*[this->_size + 10];
			this->_size = this->_size + 10;
			for(int i=0; i<_count; i++) {
				newArray[i] = this->_array[i];
				this->_array[i] = NULL;
			}
			delete this->_array;
			this->_array = newArray;
		}
		this->_array[_count] = strdup(element);
		this->_count++;
	}
	char* get(int idx) {
		char* retval = NULL;
		if(idx <= this->_count) {
			retval = this->_array[idx];
		}
		return retval;
	}
	int count() {
		return this->_count;
	}
private:
	int _size; // size of array
	int _count;// number of elements in array
	char** _array;// the array
};


#endif

