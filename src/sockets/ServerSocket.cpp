#include <sockets/IServerSocket.h>
#include <sockets/ISocket.h>

namespace httpd {
	namespace sockets {

		ServerSocket::ServerSocket(int port) {
			this->_server = new WiFiServer(port);
		}

		ServerSocket::~ServerSocket() {
			delete this->_server;
		}

		void ServerSocket::begin() {
			this->_server->begin();
		}

		ISocket* ServerSocket::available() {
			ISocket* retval = NULL;
			#ifdef ESP8266
				WiFiClient client = this->_server->available();
			#elif ARDUINO_STM32_FEATHER
				AdafruitTCP client = this->_server->available();
			#endif
			if(client) {
				retval = new Socket(client);
			}
			return retval;
		}


	}
}
