/*
 * MotorController.cpp
 *
 *  Created on: 2 feb. 2022
 *      Author: Rens
 */

#include <MotorController.h>

MotorController::MotorController() :
		nMotors(4), minValue(1000), maxValue(2000), throttleStartTarget(1150) {

	const uint8_t _motorpins[4] = { 14, 12, 13, 15 };

	for (int i = 0; i < nMotors; i++) {
		throttle[i] = minValue;
		motors[i] = new Motor(_motorpins[i], minValue, maxValue);
	}
	//Give esc some time to startup.
	delay(5000);
}

MotorController& MotorController::getMotorControllerInstance() {
	static MotorController instance;
	return instance;
}

bool MotorController::startMotors() {
	if (throttle[0] < throttleStartTarget) {
		increaseMotorsValue(10);
		delay(100);
		return false;
	} else {
		return true;
	}
}

void MotorController::stopMotors() {
	setMotorsValue(minValue);
}

void MotorController::setMotorsValue(const uint16_t value) {
	for (int i = 0; i < 4; i++) {
		setMotorValue(i, value);
	}
}

void MotorController::setMotorValue(const uint8_t motorId,
		const uint16_t value) {
	throttle[motorId] = value;
	motors[motorId]->writeMotorValue(value);
}

void MotorController::increaseMotorsValue(const uint16_t increase) {
	for (int i = 0; i < 4; i++) {
		increaseMotorValue(i, increase);
	}
}

void MotorController::increaseMotorValue(const uint8_t motorId,
		const uint16_t increase) {
	throttle[motorId] += increase;
	motors[motorId]->writeMotorValue(throttle[motorId]);
}