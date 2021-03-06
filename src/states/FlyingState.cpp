/*
 * FlyingState.cpp
 *
 *  Created on: 3 feb. 2022
 *      Author: Rens
 */

#include <states/FlyingState.h>
#include <states/FlyingIdleState.h>
#include <states/StopState.h>
#include <Arduino.h>

#include "Context.h"
#include "SerialParser.h"
#include "MotorController.h"
#include "HCSR04.h"
#include "MPU6050.h"
#include "PID.h"

FlyingState::FlyingState(Context *_context) :
		AbstractState(_context, "Flying"), Context("Flying"), pitchPID(
				new PID(0, 2.0, 0.5, 0.1, -150, 150)), rollPID(
				new PID(0, 1.5, 0.08, 0.1, -150, 150)), baseThrottle(1000), targetThrottle(
				1000), altitudeThrottle(0), throttleMotors { 1000, 1000, 1000,
				1000 }, roll(0), pitch(0), isFlying(false) {
}

FlyingState::~FlyingState() {
	if (rollPID != nullptr) {
		delete rollPID;
	}
	if (pitchPID != nullptr) {
		delete pitchPID;
	}
	if (currentState != nullptr) {
		delete currentState;
	}

}

void FlyingState::entryActivity() {
	setCurrentState(new FlyingIdleState(this));

	baseThrottle = MotorController::getMotorControllerInstance().getThrottle(0);
	targetThrottle = baseThrottle;

}

void FlyingState::doActivity() {
	IMUDriver::MPU6050::getMPU6050Instance().update();

	if (!handleSerial()) {
		return;
	}

	this->run();

	float rollMPU = IMUDriver::MPU6050::getMPU6050Instance().getRoll();
	float pitchMPU = IMUDriver::MPU6050::getMPU6050Instance().getPitch();

	if (isFlying) {
		roll = rollPID->compute(rollMPU);
		pitch = pitchPID->compute(pitchMPU);
	}

	if (targetThrottle > baseThrottle) {
		baseThrottle += 2;
	} else if (targetThrottle == 1000) {
		baseThrottle = 1000;
	}

	throttleMotors[0] = round(baseThrottle + altitudeThrottle + pitch + roll);
	throttleMotors[1] = round(baseThrottle + altitudeThrottle + pitch - roll);
	throttleMotors[2] = round(baseThrottle + altitudeThrottle - pitch - roll);
	throttleMotors[3] = round(baseThrottle + altitudeThrottle - pitch + roll);

	for (int i = 0; i < 4; i++) {
		MotorController::getMotorControllerInstance().setMotorValue(i,
				throttleMotors[i]);
	}

}

void FlyingState::exitActivity() {
	if (currentState != nullptr) {
		currentState->exitActivity();
	}
}

void FlyingState::run() {
	if (currentState != nullptr) {
		currentState->doActivity();
	}
}

void FlyingState::reset() {
	rollPID->reset();
	pitchPID->reset();
	roll = 0;
	pitch = 0;
}

void FlyingState::setIsFlying(bool isFlying) {
	this->isFlying = isFlying;
}

void FlyingState::setTargetThrottle(uint16_t targetThrottle) {
	this->targetThrottle = targetThrottle;
}

uint16_t FlyingState::getThrottle() const {
	return baseThrottle;
}

void FlyingState::setAltitudeThrottle(uint16_t altThrottle) {
	altitudeThrottle = altThrottle;
}

bool FlyingState::handleSerial() {
	if (SerialParser::getSerialParser().isMessageReady()) {
		String message = SerialParser::getSerialParser().getMessage();

		if (message == "stop") {
			SerialParser::getSerialParser().clearBuffer();
			myContext->setCurrentState(new StopState(myContext));
			return false;
		} else if (message.toInt() != 0) {
			targetThrottle = message.toInt();

			Serial.print("Received: ");
			Serial.println(targetThrottle);
			SerialParser::getSerialParser().clearBuffer();
		}
	}
	return true;
}
