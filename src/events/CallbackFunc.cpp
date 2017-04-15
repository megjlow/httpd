#include "CallbackFunc.h"

namespace httpd {

	namespace events {


		CallbackFunc::CallbackFunc(char* url, char* method, Callback callback)
		{
			this->_url = strdup(url);
			this->_callback = callback;
			this->_method = strdup(method);
		}

		CallbackFunc::CallbackFunc(char* url, Callback callback, bool wildcard) {
			this->_url = strdup(url);
			this->_callback = callback;
			this->_wildcard = wildcard;
		}

		CallbackFunc::CallbackFunc(char* url, Callback callback): CallbackFunc(url, callback, false) {
		}

		CallbackFunc::~CallbackFunc() {
			if(this->_url != NULL) {
				free(this->_url);
			}
			if(this->_method != NULL) {
				free(this->_method);
			}
		}

		Callback CallbackFunc::getCallback() {
			return this->_callback;
		}

		char* CallbackFunc::url() {
			return this->_url;
		}

		bool CallbackFunc::wildcard() {
			return this->_wildcard;
		}

		bool CallbackFunc::isMatch(char* url, char* method) {
			bool retval = false;
			if(
				(this->_wildcard && strncmp(this->_url, url, strlen(this->_url)) == 0 && (this->_method == NULL || strncmp(this->_method, method, strlen(this->_method)) == 0)) ||
				(strncmp(this->_url, url, sizeof(this->_url)) == 0 && (this->_method == NULL || strncmp(this->_method, method, strlen(this->_method)) == 0))) {
				retval = true;
			}
			return retval;
		}

	}

}
