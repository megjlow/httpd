#ifndef socketcallbackfunc_h
#define socketcallbackfunc_h

#include <Arduino.h>
//#include "sockets/WebSocket.h"
#include "sockets/SocketContext.h"

namespace httpd {

	namespace events {

		typedef void (*SocketCallback)(httpd::sockets::Socket*);

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
