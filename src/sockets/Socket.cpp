#include <sockets/Socket.h>


namespace httpd {
	namespace sockets {

#ifdef ESP8266
			Socket::Socket(WiFiClient client) {
#elif ARDUINO_STM32_FEATHER
				Socket::Socket(AdafruitTCP client) {
#endif
				this->_client = client;
				this->_isWebSocket = false;
			}

			Socket::~Socket() {
				this->_client.flush();
				this->_client.stop();
				this->_client.~Client();
			}

			int Socket::available() {
				return this->_client.available();
			}

			uint8_t Socket::connected() {
				return this->_client.connected();
			}

			size_t Socket::readBytes( char *buffer, size_t length) {
				return this->_client.readBytes(buffer, length);
			}

			size_t Socket::print(char c) {
				return this->_client.print(c);
			}

			size_t Socket::print(const char buffer[]) {
				return this->_client.print(buffer);
			}

			void Socket::flush() {
				this->_client.flush();
			}

			void Socket::stop() {
				this->_client.stop();
			}

			bool Socket::isWebSocket() {
				return this->_isWebSocket;
			}

			void Socket::setWebSocket() {
				this->_isWebSocket = true;
			}

	}
}
