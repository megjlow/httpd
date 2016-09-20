#include <sockets/ISocket.h>


namespace httpd {
	namespace sockets {

		#ifdef ESP8266

			Socket::Socket(WiFiClient client) {
				this->_client = client;
			}
		#elif ARDUINO_STM32_FEATHER
			Socket::Socket(AdafruitTCP client) {
				this->_client = client;
			}
		#endif

			Socket::~Socket() {
				Serial.println("Socket::~Socket");
				this->_client.flush();
				this->_client.stop();
				this->_client.~Client();
			}

			int Socket::available() {
				return this->_client.available();
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

	}
}
