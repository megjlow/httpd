#ifndef iserversocket_h
#define iserversocket_h

#include <sockets/ISocket.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif ARDUINO_STM32_FEATHER
#include <adafruit_feather.h>
#endif

namespace httpd {
	namespace sockets {

		class IServerSocket {
		public:
			virtual void begin();
			virtual ISocket* available();
		};

#ifdef ESP8266
	class ServerSocket: public IServerSocket {
	public:
		ServerSocket(int port);
		~ServerSocket();
		void begin();
		ISocket* available();
	private:
		WiFiServer* _server;
	};
#elif ARDUINO_STM32_FEATHER
	class ServerSocket: public IServerSocket {
	public:
		ServerSocket(int port);
		~ServerSocket();
		void begin();
		ISocket* available();
	private:
		AdafruitTCPServer* _server;
	};
#endif
	}
}

#endif
