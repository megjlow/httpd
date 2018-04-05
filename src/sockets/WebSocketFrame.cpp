#include <Arduino.h>
#include <sockets/WebSocketFrame.h>



void WebSocketFrame::dumpFrame() {
	Serial.print("fin: ");Serial.println(_fin);
	Serial.print("rsv1: ");Serial.println(_rsv1);
	Serial.print("rsv2: "); Serial.println(_rsv2);
	Serial.print("rsv3: "); Serial.println(_rsv3);
	Serial.print("opcode: "); Serial.println(_opcode);
	Serial.print("masked: "); Serial.println(_masked);
	Serial.print("length: "); Serial.println(_length);
	Serial.print("mask: [");for(int i=0; i<4; i++) { Serial.print(_mask[i], HEX); Serial.print(" "); } Serial.println("]");
	Serial.print("decoded: ["); for(int i=0; i<strlen(_body); i++) { Serial.print(_body[i], HEX); Serial.print(" "); } Serial.println("]");
}

WebSocketFrame::WebSocketFrame() {
}

/*
 * Construct a web socket frame from an incoming message
 */
WebSocketFrame::WebSocketFrame(char* message) {
	_bufferPos = 0;
	_fin = ((*message >> 7) & 0x01); // can't handle multi part messages so hope this is 0x01
	_rsv1 = ((*message >> 6) & 0x01);
	_rsv2 = ((*message >> 5) & 0x01);
	_rsv3 = ((*message >> 4) & 0x01);
	_opcode = (Opcode) (*message & 0x0F);
	message++;
	_masked = ((*message >> 7) & 0x01);
	_length = (*message & 0x7F);
	message++;
	if(_length == 126) {
		// next two bytes contain the actual length of the message
		_length = message[0] << 8 | message[1];
		message += 2;
	}
	if(_length == 127) {
		// next eight bytes contain the actual length of the message
		// at this point we should probably just explode
		_length = message[4] << 24 | message[5] << 16 | message[6] << 8 | message[7];
		message += 8;
	}
	for(int i=0; i<4; i++) {
		_mask[i] = message[i];
	}
	message += 4;
	char* body = message;
	_body = new char[_length + 1];
	for(int i=0; i<_length; i++) {
		_body[i] = (body[i] ^ _mask[i % 4]);
	}
	_body[_length] = 0;

	dumpFrame();

}

WebSocketFrame::~WebSocketFrame() {
	if(this->_body != NULL) {
		delete this->_body;
	}
}

char* WebSocketFrame::body() {
	return this->_body;
}

int WebSocketFrame::opCode() {
	return this->_opcode;
}

int WebSocketFrame::available() {
	int retval = 0;
	if(_body != NULL) {
		retval = strlen(_body) - _bufferPos;
	}
	return retval;
}

int WebSocketFrame::read() {
	int retval = -1;
	if(_body != NULL) {
		if(_bufferPos < strlen(_body)) {
			retval = _body[_bufferPos];
			_bufferPos++;
		}
	}
	return retval;
}
