#include <Arduino.h>
#include "SocketContext.h"
#include "sockets/WebSocketFrame.h"


namespace httpd {

	SocketContext::SocketContext(Socket* socket) {
		this->_socket = socket;
		int avail = socket->available();
		uint8_t buffer[avail];
		socket->readBytes((char*)buffer, avail);
		_inFrame = new WebSocketFrame((char*)buffer);
	}

	SocketContext::~SocketContext() {
		if(_inFrame != NULL) {
			delete _inFrame;
		}
		if(_outFrame != NULL) {
			delete _outFrame;
		}
	}

	char* SocketContext::getMessage() {
		return "asdf";
	}

	void SocketContext::sendMessage(char* message) {
		char mask[4] = {0};
		mask[0] = random(0xFF);
		mask[1] = random(0xFF);
		mask[2] = random(0xFF);
		mask[3] = random(0xFF);

		int messageLen = strlen(message);
		int headerLen = 6;
		if(messageLen > 126) {
			headerLen += 2;
		}

		char responseMessage[headerLen + messageLen + 1];
		for(int i=0; i<headerLen; i++) {
			responseMessage[i] = 0;
		}
		responseMessage[headerLen + messageLen] = 0;
		responseMessage[0] |= bit(7); // fin
		responseMessage[0] |= 0x01; // opcode
		responseMessage[1] |= bit(7); // mask
		responseMessage[1] |= strlen(message); // length
		responseMessage[2] = mask[0]; // mask
		responseMessage[3] = mask[1]; // mask
		responseMessage[4] = mask[2]; // mask
		responseMessage[5] = mask[3]; // mask

		char* b = &responseMessage[6];
		for(int i=0; i<messageLen; i++) {
			b[i] = (message[i] ^ mask[i % 4]);
		}
		/*
		Serial.print("sending message: [");
		for(int i=0; i<(headerLen + messageLen); i++) {
			Serial.print(responseMessage[i], HEX);
			Serial.print(" ");
		}
		Serial.println("]");
		*/

		_socket->write((uint8_t*)responseMessage, headerLen + messageLen);
		_socket->flush();
	}

}
