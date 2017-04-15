#include "SocketCallbackFunc.h"


namespace httpd {

	namespace events {

		SocketCallbackFunc::SocketCallbackFunc(SocketCallback callback) {
			this->_callback = callback;
		}

		SocketCallback SocketCallbackFunc::getCallback() {
			return this->_callback;
		}

	}

}
