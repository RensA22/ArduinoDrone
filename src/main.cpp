/*
 * main.cpp
 *
 *  Created on: Jan 19, 2022
 *      Author: rens
 */

#include <Arduino.h>
#include "FlightController.h"

//HCSR04 distSens(2, 0);
const int pins[4] = { 14, 12, 13, 15 };
FlightController fc(pins);

char incomingByte = 0;

void setup() {
	Serial.begin(115200); // Starts the serial communication
	fc.setup();
}

void loop() {
	fc.run();

	if (Serial.available() > 0) {
		incomingByte = Serial.read();

		switch (incomingByte) {
		case 's':
			fc.setCurrentState(state::start);
			break;
		case 't':
			fc.setCurrentState(state::stop);
			break;
		case 'h':
			fc.setCurrentState(state::hover);
			break;
		default:
			break;
		}
	}

}

