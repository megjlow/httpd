#ifndef SRC_SOCKETS_WEBSOCKET_H_
#define SRC_SOCKETS_WEBSOCKET_H_

#include <Stream.h>
#include "Array.h"
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
			virtual int read();
			virtual int available();

			WebSocketFrame* readMessage();
			void sendBinaryMessage(Opcode opcode, Array<char>* msg);
			void sendMessage(Opcode opcode, char* msg);
			char* getMessage();
			int opCode();
		private:
			//uint8_t* _buffer = NULL;
			Array<char>* _buffer = NULL;
			uint8_t* _inBuffer = NULL;
			uint8_t _inBufferPos = 0;
			int _inBufferSize = 0;
			WebSocketFrame* _inFrame = NULL;
			WebSocketFrame* _outFrame = NULL;
		};
	}
}


#endif
