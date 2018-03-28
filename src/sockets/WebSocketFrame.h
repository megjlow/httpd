#ifndef websocketframe_h
#define websocketframe_h

typedef enum {
	continuation = 0x00,
	text = 0x01,
	binary = 0x02,
	close = 0x08,
	ping = 0x09,
	pong = 0x0A
} Opcode;


class WebSocketFrame {
public:
	WebSocketFrame();
	WebSocketFrame(char* message);
	~WebSocketFrame();
	char* body();
	int opCode();
private:
	int _fin = 0;
	int _rsv1 = 0;
	int _rsv2 = 0;
	int _rsv3 = 0;
	int _opcode = 0;
	int _masked = 0;
	int _length = 0;
	char _mask[4] = {0};
	char* _body = NULL;
	void dumpFrame();
};

#endif
