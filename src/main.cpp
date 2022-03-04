/*
 * main.cpp
 *
 *  Created on: Jan 19, 2022
 *      Author: rens
 */

#include <Arduino.h>
#include "FlightController.h"
#include "SerialParser.h"
#include "MotorController.h"
#include "MPU6050.h"

FlightController fc;

uint64_t prevTime = 0;
uint8_t safetyPin = 2;

void setup() {
	Serial.begin(115200); // Starts the serial communications
	pinMode(safetyPin, INPUT);

	MotorController::getMotorControllerInstance().initMotors();
	MPU6050::getMPU6050Instance().setup();

	fc.setup();

}

void loop() {
//	Serial.print("LoopTime:\t");
//	Serial.print(millis() - prevTime);
//	Serial.print("\t");
//	prevTime = millis();

// Emergency stop
	if (digitalRead(safetyPin) == 1) {
		MotorController::getMotorControllerInstance().stopMotors();
		Serial.println("STOP!");
		delay(1000);
	} else {
		if (Serial.available() > 0) {
			SerialParser::getSerialParser().handleIncomingMessage(
					Serial.read());
		}
		fc.run();
	}
}
