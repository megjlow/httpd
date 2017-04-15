#ifndef socketcontext_h
#define socketcontext_h

#include <Arduino.h>
#include <sockets/Socket.h>
#include <sockets/WebSocketFrame.h>

using namespace httpd::sockets;

namespace httpd {
	class SocketContext {
		public:
			SocketContext(Socket* socket);
			~SocketContext();
			char* getMessage();
			void sendMessage(char* message);
		private:
			Socket* _socket;
			WebSocketFrame* _inFrame = NULL;
			WebSocketFrame* _outFrame = NULL;
			char* _body = NULL;
	};
}
#endif
