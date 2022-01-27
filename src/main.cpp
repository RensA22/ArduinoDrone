/*
 * main.cpp
 *
 *  Created on: Jan 19, 2022
 *      Author: rens
 */

#include <Arduino.h>
#include "FlightController.h"
//#include <RCSwitch.h>

//RCSwitch mySwitch = RCSwitch();

const int pins[4] = { 14, 12, 13, 15 };
FlightController fc(pins);

char incomingByte = 0;

void setup() {
	Serial.begin(115200); // Starts the serial communication
//	mySwitch.enableReceive(0);
	fc.setup();
}

void loop() {
	fc.run();

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

	if (Serial.available() > 0) {
		incomingByte = Serial.read();
//		Serial.println(incomingByte);

		char list[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };

		for (int i = 0; i < 9; i++) {
			if (list[i] == incomingByte) {
				fc.setMaxValue((i + 1) * 10);
			}
		}

		switch (incomingByte) {
		case 's':
			Serial.println("start");
			fc.setCurrentState(state::start);
			break;
		case 't':
			Serial.println("stop");
			fc.setCurrentState(state::stop);
			break;
		case 'h':
			Serial.println("hover");
			fc.setCurrentState(state::hover);
			break;
		case 'p':
			Serial.println("pid test");
			fc.setCurrentState(state::pid_test);
			break;
		case 'c':
//			fc.calibrate();
			break;
		default:
			break;
		}
	}

}

