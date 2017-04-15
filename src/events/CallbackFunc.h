#ifndef callbackfunc_h
#define callbackfunc_h

#include <Arduino.h>
#include "HttpContext.h"

namespace httpd {
	namespace events {

		typedef void (*Callback)(HttpContext*);

		class CallbackFunc {
		public:
			CallbackFunc(char* url, Callback callback, bool wildcard);
			CallbackFunc(char* url, Callback callback);
			~CallbackFunc();
			Callback getCallback();
			char* url();
			bool wildcard();
			bool isMatch(char* url);
		private:
			char* _url;
			Callback _callback;
			bool _wildcard;
		};

	}
}

#endif
