/*
 * main.cpp
 *
 *  Created on: Jan 19, 2022
 *      Author: rens
 */
#ifndef UNIT_TEST

#include <Arduino.h>
#include "FlightController.h"
#include "SerialParser.h"
#include "MotorController.h"
#include "Logger.h"

FlightController fc;

uint64_t prevTime = 0;
uint8_t safetyPin = 15;

void setup() {
	Serial.begin(115200); // Starts the serial communications
	pinMode(safetyPin, INPUT);

	fc.setup();
}

void loop() {
// Emergency stop
	if (digitalRead(safetyPin) == 0) {
		MotorController::getMotorControllerInstance().stopMotors();
		Logger::getLoggerInstance().log("STOP!", INFO);
		delay(1000);
	} else {
		if (Serial.available() > 0) {
			SerialParser::getSerialParser().handleIncomingMessage(
					Serial.read());
		}
		fc.run();
	}

}

#endif
