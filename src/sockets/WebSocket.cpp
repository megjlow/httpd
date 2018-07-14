#include <sockets/WebSocket.h>
#include <sockets/Socket.h>
#include "Utils.h"
#include "Array.h"


namespace httpd {
	namespace sockets {

		WebSocket::WebSocket(Socket* socket):Socket(socket) {

		}

		WebSocket::~WebSocket() {
			if(_inFrame != NULL) {
				delete _inFrame;
			}
			if(_outFrame != NULL) {
				delete _outFrame;
			}
		}

		char* WebSocket::getMessage() {
			/*
			char* retval = NULL;
			if(_request != NULL) {
				retval = _request->body();
			}
			return retval;
			*/
		}

		int WebSocket::opCode() {
			/*
			int retval = 0;
			if(_request != NULL) {
				retval = _request->opCode();
			}
			return retval;
			*/
		}

		WebSocketFrame* WebSocket::readMessage() {
			int avail = this->available();
			uint8_t buffer[avail];
			this->readBytes((char*)buffer, avail);
			return new WebSocketFrame((char*)buffer);
		}

		void WebSocket::sendBinaryMessage(Opcode opcode, Array<char>* msg) {
			int messageLen = msg->count();
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
			responseMessage[0] |= opcode;
			//responseMessage[0] = 0x81;
			//responseMessage[1] |= bit(7); // mask
			responseMessage[1] |= msg->count();

			char* b = &responseMessage[2];
			for(int i=0; i<messageLen; i++) {
				b[i] = *msg->get(i);
			}

			Serial.print("sending message: [");
			for(int i=0; i<(headerLen + messageLen + 1); i++) {
				Serial.print(responseMessage[i], HEX);
				Serial.print(" ");
			}
			Serial.println("]");

			Utils::dumpWsMessage(responseMessage);


			this->write((uint8_t*)responseMessage, headerLen + messageLen);
			//this->flush();
		}

		void WebSocket::sendMessage(Opcode opcode, char* msg) {
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
			responseMessage[0] |= opcode;
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
			for(int i=0; i<(headerLen + messageLen + 1); i++) {
				Serial.print(responseMessage[i], HEX);
				Serial.print(" ");
			}
			Serial.println("]");

			//Utils::dumpWsMessage(responseMessage);

			Serial.println("WebSocket write begin");
			this->write((uint8_t*)responseMessage, headerLen + messageLen);
			Serial.println("WebSocket write complete");
			this->flush();
		}

		void WebSocket::flush() {
			if(this->_buffer != NULL && this->_buffer->count() > 0) {
				this->sendBinaryMessage(Opcode::binary, this->_buffer);
				delete this->_buffer;
				this->_buffer = NULL;
				Socket::flush();
			}
		}

		int WebSocket::available() {
			int retval = 0;
			int avail = Socket::available();
			if(avail > 0) {
				if(_inFrame != NULL) {
					delete _inFrame;
					_inFrame = NULL;
				}
				uint8_t buffer[avail];
				for(int i=0; i<avail; i++) {
					buffer[i] = 0;
				}
				this->readBytes((char*)buffer, avail);

				_inFrame = new WebSocketFrame((char*)buffer);
				retval = _inFrame->available();
			}
			else if(_inFrame != NULL){
				retval = _inFrame->available();
			}
			return retval;
		}

		int WebSocket::read() {
			return _inFrame->read();
		}

		size_t WebSocket::readBytes(char *buffer, size_t length) {
			return Socket::readBytes(buffer, length);
		}

		size_t WebSocket::write(uint8_t byte) {
			size_t retval = 0;
			if(this->_buffer == NULL) {
				this->_buffer = new Array<char>();
			}
			this->_buffer->add((char*)&byte);
			retval = 1;

			return retval;
		}

		size_t WebSocket::write(const uint8_t *buf, size_t size) {
			Socket::write(buf, size);
		}

	}
}
