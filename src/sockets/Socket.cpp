#include <sockets/Socket.h>

#include "Firmata.h"

namespace httpd {
	namespace sockets {

#ifdef ESP8266
			Socket::Socket(WiFiClient client) {
#elif ARDUINO_STM32_FEATHER
				Socket::Socket(AdafruitTCP client) {
#endif
				this->_client = client;
			}

			Socket::Socket(const Socket* socket) {
				this->_client = socket->_client;
			}

			Socket::~Socket() {
				Serial.println("Socket destructor");
				this->_client.flush();
				this->_client.stop();
				this->_client.~Client();
			}

			int Socket::available() {
				return _client.available();
			}

			uint8_t Socket::connected() {
				return this->_client.connected();
			}

			size_t Socket::readBytes(char *buffer, size_t length) {
				return this->_client.readBytes(buffer, length);
			}

			size_t Socket::print(char c) {
				return this->_client.print(c);
			}

			size_t Socket::print(const char buffer[]) {
				return this->_client.print(buffer);
			}

			size_t Socket::write(const uint8_t *buf, size_t size) {
				return this->_client.write(buf, size);
			}

			void Socket::flush() {
				this->_client.flush();
			}

			void Socket::stop() {
				this->_client.stop();
			}

			uint8_t Socket::status() {
				return this->_client.status();
			}

			void Socket::setNoDelay(bool nodelay) {
				this->_client.setNoDelay(nodelay);
			}

			bool Socket::getNoDelay() {
				return this->_client.getNoDelay();
			}

			size_t Socket::write(uint8_t byte) {
				this->_client.write(byte);
			}

			int Socket::read() {
				return this->_client.read();
			}

			int Socket::peek() {
				return this->_client.peek();
			}

	}
}
