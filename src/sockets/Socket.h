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
			uint8_t connected();
			size_t readBytes( char *buffer, size_t length);
			size_t print(char);
			size_t print(const char[]);
			size_t write(const uint8_t *buf, size_t size);
			void setNoDelay(bool noDelay);
			void flush();
			void stop();
			void setWebSocket();
			bool isWebSocket();
		private:
#ifdef ESP8266
				WiFiClient _client;
#elif ARDUINO_STM32_FEATHER
				AdafruitTCP _client;
#endif
			bool _isWebSocket;
		};

	}
}

#endif
