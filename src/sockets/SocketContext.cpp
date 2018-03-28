#include <Arduino.h>
#include "SocketContext.h"
#include "sockets/WebSocketFrame.h"

#include "Firmata.h"
#include "Stream.h"


namespace httpd {
	namespace sockets {

		SocketContext::SocketContext(Socket* socket) {
			this->_socket = socket;
			int avail = socket->available();
			uint8_t buffer[avail];
			socket->readBytes((char*)buffer, avail);
			_inFrame = new WebSocketFrame((char*)buffer);

			//Firmata.setFirmwareVersion(FIRMATA_FIRMWARE_MAJOR_VERSION, FIRMATA_FIRMWARE_MINOR_VERSION);
			//Firmata.begin(socket[0]);
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
			char* retval = NULL;
			if(_inFrame != NULL) {
				retval = _inFrame->body();
			}
			return retval;
		}

		int SocketContext::opCode() {
			int retval = 0;
			if(_inFrame != NULL) {
				retval = _inFrame->opCode();
			}
			return retval;
		}

		void SocketContext::sendPong(char* message) {
			int messageLen = strlen(message);
			int headerLen = 2;

			if(messageLen > 126) {
				headerLen += 2;
			}

			char responseMessage[headerLen + messageLen + 1];
			for(int i=0; i<headerLen; i++) {
				responseMessage[i] = 0;
			}
			responseMessage[headerLen + messageLen] = 0;
			responseMessage[0] |= bit(7); // fin
			responseMessage[0] |= 0x0a; // opcode
			responseMessage[1] |= strlen(message); // length

			char* b = &responseMessage[2];
			for(int i=0; i<messageLen; i++) {
				b[i] = message[i];
			}

			Serial.print("sending message: [");
			for(int i=0; i<(headerLen + messageLen); i++) {
				Serial.print(responseMessage[i], HEX);
				Serial.print(" ");
			}
			Serial.println("]");


			_socket->write((uint8_t*)responseMessage, headerLen + messageLen);
			_socket->flush();
		}

		void SocketContext::sendMessage(char* message) {
			int messageLen = strlen(message);
			int headerLen = 2;
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
			//responseMessage[0] = 0x81;
			//responseMessage[1] |= bit(7); // mask
			responseMessage[1] |= strlen(message); // length

			//char* b = &responseMessage[6];
			//for(int i=0; i<messageLen; i++) {
				//b[i] = (message[i] ^ mask[i % 4]);
			//}
			char* b = &responseMessage[2];
			for(int i=0; i<messageLen; i++) {
				b[i] = message[i];
			}

			Serial.print("sending message: [");
			for(int i=0; i<(headerLen + messageLen); i++) {
				Serial.print(responseMessage[i], HEX);
				Serial.print(" ");
			}
			Serial.println("]");


			_socket->write((uint8_t*)responseMessage, headerLen + messageLen);
			_socket->flush();
		}

	}

}
