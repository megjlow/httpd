#include <Arduino.h>
#include <sockets/WebSocketFrame.h>



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

uint8_t* WebSocketFrame::parseFrame(uint8_t* message) {
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
	uint8_t* body = message;
	/*
	_body = new char[_length + 1];
	for(int i=0; i<_length; i++) {
		_body[i] = (body[i] ^ _mask[i % 4]);
	}
	_body[_length] = 0;
	*/

	uint8_t* retval = new uint8_t[_length + 1];
	for(int i=0; i<_length; i++) {
		retval[i] = (body[i] ^ _mask[i % 4]);
	}
	retval[_length] = 0;
	return retval;
}

/*
 * Construct a web socket frame from an incoming message
 */
WebSocketFrame::WebSocketFrame(uint8_t* message, int length) {
	for(int i=0; i<length; i++) {
		if(message[i] == 0x82) {
			Serial.print("frame starts at "); Serial.println(i);
			int bodyLen = _length;
			_totalLength = length;
			uint8_t* msg = parseFrame(&message[i]);
			if(_body == NULL) {
				_body = (char*) msg;
			}
			else {
				int newLength = bodyLen + _length + 1;
				char* tempBody = new char[newLength];
				for(int j=0; j<bodyLen; j++) { // copy original message into _body
					tempBody[j] = _body[j];
				}
				for(int j=0; j < _length; j++) {
					tempBody[bodyLen + j] = msg[j];
				}
				tempBody[sizeof(tempBody)] = 0;

				delete this->_body;
				_body = tempBody;
				_totalLength = newLength;
			}
		}
	}

	_bufferPos = 0;


	//dumpFrame();

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
		retval = _totalLength - _bufferPos;
	}
	return retval;
}

int WebSocketFrame::read() {
	int retval = -1;
	if(_body != NULL) {
		if(_bufferPos < _length) {
			retval = _body[_bufferPos];
			_bufferPos++;
		}
	}
	return retval;
}
