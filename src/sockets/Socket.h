#ifndef isocket_h
#define isocket_h

#include <sockets/Socket.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif ARDUINO_STM32_FEATHER
#include <adafruit_feather.h>
#endif


namespace httpd {

	namespace sockets {

		class Socket {
		public:
#ifdef ESP8266
				Socket(WiFiClient client);
#elif ARDUINO_STM32_FEATHER
				Socket(AdafruitTCP client);
#endif
			~Socket();
			int available();
			size_t readBytes( char *buffer, size_t length);
			size_t print(char);
			size_t print(const char[]);
			void flush();
			void stop();
		private:
#ifdef ESP8266
				WiFiClient _client;
#elif ARDUINO_STM32_FEATHER
				AdafruitTCP _client;
#endif
		};

	}
}

#endif
