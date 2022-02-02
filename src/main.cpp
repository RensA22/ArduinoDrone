/*
 * main.cpp
 *
 *  Created on: Jan 19, 2022
 *      Author: rens
 */

#include <Arduino.h>
#include "FlightController.h"
#include "SerialParser.h"

uint64_t prevTime = 0;

FlightController fc;

void setup() {
	Serial.begin(115200); // Starts the serial communication
	pinMode(2, INPUT);
	fc.setup();
//	fc.setCurrentState(state::HOVER);
//	Serial.println("10 sec");
//	delay(10000);
//	Serial.println("2 sec");
//	delay(2000);

}

void loop() {
//	Serial.print("LoopTime: ");
//	Serial.println(millis() - prevTime);
//	prevTime = millis();

	fc.run();
// Emergency stop
	if (digitalRead(2) == 1 && false) {
		Serial.println("STOPPPPPP");
//		fc.setCurrentState(state::STOP);
	} else {

		if (Serial.available() > 0) {
			SerialParser::getSerialParser().handleIncomingMessage(
					Serial.read());
		}
	}
}

