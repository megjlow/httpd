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
		};

#ifdef ESP8266
		class Socket: public ISocket {
		public:
			Socket(WiFiClient client);
			int available();
			size_t readBytes( char *buffer, size_t length);
			size_t print(char);
			size_t print(const char[]);
		private:
			WiFiClient _client;
		};
#elif ARDUINO_STM32_FEATHER
	class Socket: public ISocket {
	public:
		Socket(AdafruitTCP client);
		int available();
		size_t readBytes( char *buffer, size_t length);
		size_t print(char);
		size_t print(const char[]);
	private:
		AdafruitTCP _client;
	};
#endif
	}
}

#endif
