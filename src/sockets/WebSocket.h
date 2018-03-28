#ifndef SRC_SOCKETS_WEBSOCKET_H_
#define SRC_SOCKETS_WEBSOCKET_H_

#include <Stream.h>
#include "sockets/Socket.h"
#include "sockets/WebSocketFrame.h"

namespace httpd {

	namespace sockets {

		class WebSocket: public Socket {
		public:
			WebSocket(Socket* socket);
			~WebSocket();
			virtual size_t write(uint8_t byte);
			virtual size_t write(const uint8_t *buf, size_t size);
			virtual size_t readBytes(char *buffer, size_t length);

			WebSocketFrame* readMessage();
			void sendTextMessage(char* msg);
		private:
			uint8_t* _buffer = NULL;
			uint8_t _bufferPosition = 0;
		};
	}
}


#endif
