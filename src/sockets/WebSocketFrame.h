#include <sockets/Frame.h>

#ifndef websocketframe_h
#define websocketframe_h

enum Opcode {
	continuation = 0x00,
	text = 0x01,
	binary = 0x02,
	close = 0x08,
	ping = 0x09,
	pong = 0x0A
};


class WebSocketFrame {
public:
	WebSocketFrame();
	WebSocketFrame(uint8_t* message, int length);
	WebSocketFrame(Opcode opcode, char* message);
	~WebSocketFrame();
	uint8_t* body();
	int opCode();
	int read();
	int available();
private:
	int _fin = 0;
	int _rsv1 = 0;
	int _rsv2 = 0;
	int _rsv3 = 0;
	int _opcode = 0;
	int _masked = 0;
	int _length = 0;
	char _mask[4] = {0};
	uint8_t* _body = NULL;
	//uint8_t* _tempBody = NULL;
	//int _tempLength = 0;
	//int _parsedMessageLength = 0;
	int _bufferPos = 0;
	Frame* parseFrame(uint8_t* message);
	void dumpFrame();
};

#endif
