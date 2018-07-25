#ifndef SRC_SOCKETS_FRAME_H_
#define SRC_SOCKETS_FRAME_H_


class Frame {
	public:
		//WebSocketFrame(uint8_t* message, int length);
		Frame(uint8_t* data, int length);
		~Frame();
		int length();
		uint8_t* data();
		void dump();
	private:
		int _length = 0;
		uint8_t* _data = NULL;
};

#endif
