/*
 * SerialParser.cpp
 *
 *  Created on: 28 jan. 2022
 *      Author: Rens
 */

#include <Arduino.h>
#include "SerialParser.h"

SerialParser& SerialParser::getSerialParser() {
	static SerialParser instance;
	return instance;
}

void SerialParser::handleIncomingMessage(char incomingMessage) {
	if ((int16_t) incomingMessage == 10) {
		if (bufferFull) {
			clearBuffer();
			bufferFull = false;
		} else {
			messageReady = true;
		}
	} else {
		buffer[bufferIndex] = incomingMessage;
		++bufferIndex;
		if (bufferIndex > bufferSize) {
			Serial.println("Text to long for buffer. MAX 10 characters");
			bufferFull = true;
		}
	}
}

String SerialParser::getMessage() {
	String message = String(buffer);
	return message;
}

void SerialParser::clearBuffer() {
	memset(buffer, 0, bufferSize);
	bufferIndex = 0;
	messageReady = false;
}

bool SerialParser::isMessageReady() const {
	return messageReady;
}
