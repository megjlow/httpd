#ifndef isocket_h
#define isocket_h

#include <sockets/ISocket.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif ARDUINO_STM32_FEATHER
#include <adafruit_feather.h>
#endif


namespace httpd {

	namespace sockets {

		class ISocket {
		public:
			virtual int available();
			virtual size_t readBytes( char *buffer, size_t length);
			virtual size_t print(char);
			virtual size_t print(const char[]);
			virtual void flush();
			virtual void stop();
		};


		class Socket: public ISocket {
		public:
			#ifdef ESP8266
				Socket(WiFiClient client);
			#elif ARDUINO_STM32_FEATHER
				Socket(AdafruitTCP client);
			#endif
			virtual ~Socket();
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
