#include <sockets/IServerSocket.h>
#include <sockets/ISocket.h>

namespace httpd {
	namespace sockets {

		ServerSocket::ServerSocket(int port) {
#ifdef ESP8266
			this->_server = new WiFiServer(port);
#elif ARDUINO_STM32_FEATHER
			this->_server = new AdafruitTCPServer(port);
			this->_server->err_actions(true, false);
#endif

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
				if(client) {
			#elif ARDUINO_STM32_FEATHER
				AdafruitTCP client = this->_server->available();
				if(client.valid()) {
			#endif
				Serial.println("new client");
				retval = new Socket(client);
			}
			return retval;
		}


	}
}
