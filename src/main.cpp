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

uint64_t prevTime = 0;

//FlightController fc;

void setup() {
	Serial.begin(115200); // Starts the serial communications

//	fc.setup();
//	pinMode(2, INPUT);

	MPU6050::getMPU6050Instance().setup();
}

void loop() {
	MPU6050::getMPU6050Instance().update();
//	Serial.print("LoopTime: ");
//	Serial.println(millis() - prevTime);
//	prevTime = millis();

// Emergency stop
//	if (digitalRead(2) == 1) {
//		MotorController::getMotorControllerInstance().stopMotors();
//		Serial.println("STOP!");
//		delay(1000);
//	} else {
//		if (Serial.available() > 0) {
//			SerialParser::getSerialParser().handleIncomingMessage(
//					Serial.read());
//		}
//		fc.run();
//	}
}

