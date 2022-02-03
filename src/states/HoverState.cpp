/*
 * HoverState.cpp
 *
 *  Created on: 3 feb. 2022
 *      Author: Rens
 */

#include <states/HoverState.h>
#include <states/StopState.h>

#include "MPU6050.h"
#include "MotorController.h"

HoverState::HoverState(Context *_context) :
		AbstractState(_context) {
}

void HoverState::entryActivity() {
	Serial.println("Entry flying Hover");
}

void HoverState::doActivity() {

	float angleX = round(MPU6050::getMPU6050Instance().getAngleX());
//	float out = rollPID->compute(angleX);
	float out = 0;

	uint16_t throttle = 1500;

	int16_t motorLinks = round(throttle - out);
	int16_t motorRechts = round(throttle + out);

	MotorController::getMotorControllerInstance().setMotorValue(0, motorLinks);
	MotorController::getMotorControllerInstance().setMotorValue(1, motorRechts);
	MotorController::getMotorControllerInstance().setMotorValue(2, motorRechts);
	MotorController::getMotorControllerInstance().setMotorValue(3, motorLinks);

	Serial.print("Angle: ");
	Serial.print(angleX);
	Serial.print(" ,MotorLinks: ");
	Serial.print(motorLinks);
	Serial.print(" ,motorRechts: ");
	Serial.println(motorRechts);
}

void HoverState::exitActivity() {
}
