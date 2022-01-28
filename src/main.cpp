/*
 * main.cpp
 *
 *  Created on: Jan 19, 2022
 *      Author: rens
 */

#include <Arduino.h>
#include "FlightController.h"
#include "SerialParser.h"
//#include <RCSwitch.h>

//RCSwitch mySwitch = RCSwitch();
uint64_t prevTime = 0;

const int pins[4] = { 14, 12, 13, 15 };
FlightController fc(pins);
//SerialParser par;

char incomingString;

void setup() {
	Serial.begin(115200); // Starts the serial communication
//	mySwitch.enableReceive(0);
	pinMode(2, INPUT);
	fc.setup();
	fc.setCurrentState(state::hover);
	Serial.println("10 sec");
	delay(10000);
	Serial.println("2 sec");
	delay(2000);
}

void loop() {
	Serial.print("LoopTime: ");
	Serial.println(millis() - prevTime);
	prevTime = millis();

	fc.run();
// Emergency stop
	if (digitalRead(2) == 1) {
		Serial.println("STOPPPPPP");
		fc.setCurrentState(state::stop);
	} else {

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
	}

//	if (mySwitch.available()) {
//		Serial.println(mySwitch.getReceivedValue());
//
//		char list[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
//
//		for (int i = 0; i < 9; i++) {
//			if (list[i] == mySwitch.getReceivedValue()) {
//				fc.setMaxValue((i + 1) * 10);
//			}
//		}
//
//		switch (mySwitch.getReceivedValue()) {
//		case 's':
//			fc.setCurrentState(state::start);
//			break;
//		case 't':
//			fc.setCurrentState(state::stop);
//			break;
//		case 'h':
//			fc.setCurrentState(state::hover);
//			break;
//		case 'p':
//			fc.setCurrentState(state::pid_test);
//			break;
//		default:
//			break;
//		}
//		mySwitch.resetAvailable();
//	}

}

