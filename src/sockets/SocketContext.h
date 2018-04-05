#ifndef socketcontext_h
#define socketcontext_h

#include <Arduino.h>
#include <sockets/Socket.h>
#include <sockets/WebSocketFrame.h>


namespace httpd {
	namespace sockets {
		class SocketContext {
			public:
				SocketContext(Socket* socket);
				~SocketContext();
				char* getMessage();
				void sendTextMessage(char* message);
				void sendMessage(Opcode opcode, char* message);
				int opCode();
				void sendPong(char* message);
			private:
				Socket* _socket;
				WebSocketFrame* _request = NULL;
				WebSocketFrame* _response = NULL;
				char* _body = NULL;
		};
	}
}
#endif
