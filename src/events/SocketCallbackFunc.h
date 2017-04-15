#ifndef socketcallbackfunc_h
#define socketcallbackfunc_h

#include <Arduino.h>
#include <SocketContext.h>

namespace httpd {

	namespace events {

		typedef void (*SocketCallback)(SocketContext*);

		class SocketCallbackFunc {
		public:
			SocketCallbackFunc(SocketCallback callback);
			~SocketCallbackFunc();
			SocketCallback getCallback();
		private:
			SocketCallback _callback;
		};

	}

}

#endif
