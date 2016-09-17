#include <sockets/IServerSocket.h>
#include <sockets/ISocket.h>

namespace httpd {
	namespace sockets {

#ifdef ESP8266
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
			WiFiClient client = this->_server->available();
			if(client) {
				retval = new Socket(client);
			}
			return retval;
		}
#elif ARDUINO_STM32_FEATHER
		ServerSocket::ServerSocket(int port) {
			this->_server = new AdafruitTCPServer(port);
		}

		ServerSocket::~ServerSocket() {
			delete this->_server;
		}

		void ServerSocket::begin() {
			this->_server->begin();
		}

		ISocket* ServerSocket::available() {
			AdafruitTCP client = this->_server->available();
			Socket* s = new Socket(client);
			return (ISocket*)s;
		}
#endif


	}
}
