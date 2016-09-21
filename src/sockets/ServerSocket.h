#ifndef iserversocket_h
#define iserversocket_h

#include <sockets/Socket.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif ARDUINO_STM32_FEATHER
#include <adafruit_feather.h>
#endif

namespace httpd {
	namespace sockets {

		class ServerSocket {
		public:
			ServerSocket(int port);
			~ServerSocket();
			void begin();
			Socket* available();
		private:
#ifdef ESP8266
			WiFiServer* _server;
#elif ARDUINO_STM32_FEATHER
			AdafruitTCPServer* _server;
#endif
		};

	}
}

#endif
