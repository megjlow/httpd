#ifndef callbackfunc_h
#define callbackfunc_h

#include <Arduino.h>
#include "HttpContext.h"

namespace httpd {
	namespace events {

		typedef void (*Callback)(HttpContext*);

		class CallbackFunc {
		public:
			CallbackFunc(char* url, char* method, Callback callback);
			CallbackFunc(char* url, Callback callback, bool wildcard);
			CallbackFunc(char* url, Callback callback);
			~CallbackFunc();
			Callback getCallback();
			char* url();
			bool wildcard();
			bool isMatch(char* url, char* operation);
		private:
			char* _url = NULL;
			Callback _callback = NULL;
			bool _wildcard = false;
			char* _method = NULL;
		};

	}
}

#endif
