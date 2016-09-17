#include <sockets/ISocket.h>


namespace httpd {
	namespace sockets {

		#ifdef ESP8266

			Socket::Socket(WiFiClient client) {
				this->_client = client;
			}

			int Socket::available() {
				return _client.available();
			}

			size_t Socket::readBytes( char *buffer, size_t length) {
				return _client.readBytes(buffer, length);
			}

			size_t Socket::print(char c) {
				return _client.print(c);
			}

			size_t Socket::print(const char buffer[]) {
				return _client.print(buffer);
			}

			void Socket::flush() {
				_client.flush();
			}

			void Socket::stop() {
				_client.stop();
			}

#elif ARDUINO_STM32_FEATHER
			Socket::Socket(AdafruitTCP client) {
				this->_client = client;
			}

			int Socket::available() {
				return _client.available();
			}

			size_t Socket::readBytes( char *buffer, size_t length) {
				return _client.readBytes(buffer, length);
			}

			size_t Socket::print(char c) {
				return _client.print(c);
			}

			size_t Socket::print(const char buffer[]) {
				return _client.print(buffer);
			}

			void Socket::flush() {
				_client.flush();
			}

			void Socket::stop() {
				_client.stop();
			}

		#endif

	}
}
