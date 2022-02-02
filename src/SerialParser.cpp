/*
 * SerialParser.cpp
 *
 *  Created on: 28 jan. 2022
 *      Author: Rens
 */

#include <Arduino.h>
#include "SerialParser.h"

//		if (Serial.available() > 0) {
////			par.parseText(Serial.readString());
////			//		Serial.println(incomingByte);
////
////			char list[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
////
////			for (int i = 0; i < 9; i++) {
////				if (list[i] == incomingByte) {
////					fc.setMaxValue((i + 1) * 10);
////				}
////			}
//
//			incomingString = Serial.read();
//
////			if (incomingString == "s") {
////				Serial.println("start");
////				fc.setCurrentState(state::start);
////			} else if (incomingString == "t") {
////				Serial.println("stop");
////				fc.setCurrentState(state::stop);
////			} else if (incomingString == "h") {
////				Serial.println("hover");
////				fc.setCurrentState(state::hover);
////			} else {
////				Serial.println("motor value");
////				fc.setMotorsValue(incomingString.toInt());
////			}
//
//			switch (incomingString) {
//			case 's':
//				Serial.println("start");
//				fc.setCurrentState(state::start);
//				break;
//			case 't':
//				Serial.println("stop");
//				fc.setCurrentState(state::stop);
//				break;
//			case 'h':
//				Serial.println("hover");
//				fc.setCurrentState(state::hover);
//				break;
//			case 'p':
//				Serial.println("pid test");
//				fc.setCurrentState(state::pid_test);
//				break;
//			case 'c':
//				//			fc.calibrate();
//				break;
//			default:
//				break;
//			}
//		}

SerialParser& SerialParser::getSerialParser() {
	static SerialParser instance;
	return instance;
}

void SerialParser::handleIncomingMessage(char incomingMessage) {
	if ((int16_t) incomingMessage == 10) {
		if (bufferFull) {
			clearBuffer();
		} else {
			messageReady = true;
		}
	} else {
		buffer[bufferIndex] = incomingMessage;
		++bufferIndex;
		if (bufferIndex > bufferSize) {
			Serial.println("Text to long for buffer. MAX 10 characters");
			clearBuffer();
			bufferFull = true;
		}
	}
}

String SerialParser::getMessage() {
	String message = String(buffer);
	clearBuffer();
	messageReady = false;
	return message;
}

void SerialParser::clearBuffer() {
	memset(buffer, 0, bufferSize);
	bufferIndex = 0;
}

bool SerialParser::isMessageReady() const {
	return messageReady;
}
