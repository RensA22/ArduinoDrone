/*
 * HoverState.cpp
 *
 *  Created on: 3 feb. 2022
 *      Author: Rens
 */

#include <states/HoverState.h>

HoverState::HoverState(Context *_context) :
		AbstractState(_context, "Hover") {
}
HoverState::~HoverState() {

}

void HoverState::entryActivity() {
	// give myself time to hold the drone steady
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
