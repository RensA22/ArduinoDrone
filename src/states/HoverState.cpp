/*
 * HoverState.cpp
 *
 *  Created on: 3 feb. 2022
 *      Author: Rens
 */

#include <states/HoverState.h>
#include <states/StopState.h>
#include <states/FlyingState.h>

#include "MPU6050.h"
#include "MotorController.h"
#include "SerialParser.h"

HoverState::HoverState(Context *_context) :
		AbstractState(_context, "Hover"), rollPID(
				new PID(0, 0.05, 0.005, 0.02, -1000, 1000)), pitchPID(
				new PID(0, 0.05, 0.005, 0.02, -1000, 1000)) {
}

HoverState::~HoverState() {
	delete rollPID;
	delete pitchPID;
}

void HoverState::entryActivity() {
	// give myself time to hold the drone steady
	Serial.println("5 sec");
	delay(5000);
}

void HoverState::doActivity() {

//	float angleX = MPU6050::getMPU6050Instance().getAngleX();
////	if (angleX >= -3 && angleX <= 3) {
////		angleX = 0;
////	}
//
//	float out = rollPID->compute(angleX);
//
//	uint16_t throttle = 1300;
//
//	int16_t motorLinks = round(throttle - out);
//	int16_t motorRechts = round(throttle + out);
//
//	MotorController::getMotorControllerInstance().setMotorValue(0, motorLinks);
//	MotorController::getMotorControllerInstance().setMotorValue(1, motorRechts);
//	MotorController::getMotorControllerInstance().setMotorValue(2, motorRechts);
//	MotorController::getMotorControllerInstance().setMotorValue(3, motorLinks);
//
//	Serial.print("Angle: ");
//	Serial.print(angleX);
//	Serial.print(" ,PID: ");
//	Serial.print(out);
//	Serial.print(" ,MotorLinks: ");
//	Serial.print(motorLinks);
//	Serial.print(" ,motorRechts: ");
//	Serial.println(motorRechts);
}

void HoverState::exitActivity() {
}
