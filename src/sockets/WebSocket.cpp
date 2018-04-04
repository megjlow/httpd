#include <sockets/WebSocket.h>
#include <sockets/Socket.h>
#include "Utils.h"
#include <Firmata.h>


namespace httpd {
	namespace sockets {

		WebSocket::WebSocket(Socket* socket):Socket(socket) {

		}

		WebSocket::~WebSocket() {

		}

		WebSocketFrame* WebSocket::readMessage() {
			int avail = this->available();
			uint8_t buffer[avail];
			this->readBytes((char*)buffer, avail);
			return new WebSocketFrame((char*)buffer);
		}

		void WebSocket::sendTextMessage(char* msg2) {
			char* msg = (char*) malloc(strlen(msg2) * 3 + 1);
			Utils::urlEncode(msg, msg2);
			int messageLen = strlen(msg);
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
			responseMessage[1] |= strlen(msg); // length

			//char* b = &responseMessage[6];
			//for(int i=0; i<messageLen; i++) {
				//b[i] = (message[i] ^ mask[i % 4]);
			//}
			char* b = &responseMessage[2];
			for(int i=0; i<messageLen; i++) {
				b[i] = msg[i];
			}

			Serial.print("sending message: [");
			for(int i=0; i<(headerLen + messageLen); i++) {
				Serial.print(responseMessage[i], HEX);
				Serial.print(" ");
			}
			Serial.println("]");

			Utils::dumpWsMessage(responseMessage);


			this->write((uint8_t*)responseMessage, headerLen + messageLen);
			this->flush();
		}

		size_t WebSocket::readBytes(char *buffer, size_t length) {
			return Socket::readBytes(buffer, length);
		}

		size_t WebSocket::write(uint8_t byte) {
			size_t retval = 0;
			if(this->_buffer == NULL) {
				this->_buffer = (uint8_t*) calloc(64, sizeof(uint8_t));
				this->_buffer[0] = byte;
				this->_bufferPosition = 1;
			}
			else {
				this->_buffer[this->_bufferPosition] = byte;
				this->_bufferPosition++;
			}
			retval = 1;
			if(byte == END_SYSEX) {
				//this->write(_buffer, _bufferPosition -1);
				this->sendTextMessage((char*)_buffer);
				_bufferPosition = 0;
			}
			return retval;
		}

		size_t WebSocket::write(const uint8_t *buf, size_t size) {
			Socket::write(buf, size);
		}

	}
}
