#include <Arduino.h>
#include <sockets/WebSocketFrame.h>
#include <Array.h>

#include <sockets/Frame.h>



void WebSocketFrame::dumpFrame() {
	Serial.println("<received>");
	Serial.print("fin: ");Serial.println(_fin);
	//Serial.print("rsv1: ");Serial.println(_rsv1);
	Serial.print("rsv2: "); Serial.println(_rsv2);
	Serial.print("rsv3: "); Serial.println(_rsv3);
	Serial.print("opcode: "); Serial.println(_opcode);
	Serial.print("masked: "); Serial.println(_masked);
	Serial.print("length: "); Serial.println(_length);
	Serial.print("mask: [");for(int i=0; i<4; i++) { Serial.print(_mask[i], HEX); Serial.print(" "); } Serial.println("]");
	Serial.print("decoded: ["); for(int i=0; i<_length; i++) { Serial.print(_body[i], HEX); Serial.print(" "); } Serial.println("]");
	Serial.println("</received>");
}

WebSocketFrame::WebSocketFrame() {
}

Frame* WebSocketFrame::parseFrame(uint8_t* message) {
	int fin = ((*message >> 7) & 0x01); // can't handle multi part messages so hope this is 0x01
	int rsv1 = ((*message >> 6) & 0x01);
	int rsv2 = ((*message >> 5) & 0x01);
	int rsv3 = ((*message >> 4) & 0x01);
	int opcode = (Opcode) (*message & 0x0F);
	message++;
	int masked = ((*message >> 7) & 0x01);
	int length = (*message & 0x7F);
	message++;
	if(length == 126) {
		// next two bytes contain the actual length of the message
		length = message[0] << 8 | message[1];
		message += 2;
	}
	if(length == 127) {
		// next eight bytes contain the actual length of the message
		// at this point we should probably just explode
		length = message[4] << 24 | message[5] << 16 | message[6] << 8 | message[7];
		message += 8;
	}
	for(int i=0; i<4; i++) {
		_mask[i] = message[i];
	}
	message += 4;
	uint8_t* body = message;

	uint8_t* retval = new uint8_t[length + 1];
	for(int i=0; i<length; i++) {
		retval[i] = (body[i] ^ _mask[i % 4]);
	}
	retval[length] = 0;

	Frame* frame = new Frame(retval, length);
	return frame;
}

/*
 * Construct a web socket frame from an incoming message
 */
WebSocketFrame::WebSocketFrame(uint8_t* message, int length) {
	/*
	Serial.println("<WebSocketFrame>");
	for(int i=0; i<length; i++) {
		Serial.print(message[i], HEX); Serial.print(" ");
	}
	Serial.println("");
	Serial.println("</WebSocketFrame>");
	*/

	uint8_t* msgBody;
	int msgLength;
	Array<Frame>* frames = new Array<Frame>();
	Frame* frame = parseFrame(message);
	frames->add(frame);
	int parsedLength = frame->length() + 6; // add six because that's the size of the frame header
	frame->dump();
	Serial.print("parsed "); Serial.println(parsedLength);
	while(parsedLength < length) {
		Frame* f = parseFrame(&message[parsedLength]);
		frames->add(f);
		parsedLength = parsedLength + f->length() + 6;
		f->dump();
		Serial.print("parsed "); Serial.println(parsedLength);
	}

	int totalLength = 0;
	for(int i=0; i<frames->count(); i++) {
		totalLength += frames->get(i)->length();
	}
	_body = new uint8_t[totalLength];
	int pos = 0;
	for(int i=0; i<frames->count(); i++) {
		Frame* f = frames->get(i);
		for(int j=0; j<f->length(); j++) {
			_body[pos] = f->data()[j];
			pos++;
		}
	}
	_length = pos;

	Serial.print("<WebSocketFrame> ");
	for(int i=0; i<pos; i++) {
		Serial.print(_body[i], HEX); Serial.print(" ");
	}
	Serial.println("</WebSocketFrame>");
	delete frames;

	_bufferPos = 0;


	//dumpFrame();

}

WebSocketFrame::~WebSocketFrame() {
	if(this->_body != NULL) {
		delete this->_body;
	}
}

uint8_t* WebSocketFrame::body() {
	return this->_body;
}

int WebSocketFrame::opCode() {
	return this->_opcode;
}

int WebSocketFrame::available() {
	int retval = 0;
	if(_body != NULL && _length > 0) {
		retval = _length - _bufferPos;
	}
	return retval;
}

int WebSocketFrame::read() {
	int retval = -1;
	if(_body != NULL && _length > 0) {
		if(_bufferPos < _length) {
			retval = _body[_bufferPos];
			_bufferPos++;
		}
	}
	return retval;
}
