#ifndef isocket_h
#define isocket_h

#include <Stream.h>
#include <sockets/Socket.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif ARDUINO_STM32_FEATHER
#include <adafruit_feather.h>
#endif


namespace httpd {

	namespace sockets {

		class Socket: public Stream {
		public:
#ifdef ESP8266
				Socket(WiFiClient client);
#elif ARDUINO_STM32_FEATHER
				Socket(AdafruitTCP client);
#endif
			Socket(const Socket* obj);
			~Socket();
			virtual int available();
			uint8_t connected();
			virtual size_t readBytes( char *buffer, size_t length);
			size_t print(char);
			size_t print(const char[]);
			virtual size_t write(const uint8_t *buf, size_t size);
			void flush();
			void stop();
			uint8_t status();
			void setNoDelay(bool nodelay);
			bool getNoDelay();

			virtual size_t write(uint8_t byte);
			virtual int read();
			virtual int peek();

		private:
#ifdef ESP8266
				WiFiClient _client;
#elif ARDUINO_STM32_FEATHER
				AdafruitTCP _client;
#endif
		protected:

		};

	}
}

#endif
