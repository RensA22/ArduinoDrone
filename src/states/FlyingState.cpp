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
#include "MPU6050.h"
#include "MotorController.h"

FlyingState::FlyingState(Context *_context) :
		AbstractState(_context, "Flying"), Context("Flying"), pitchPID(
				new PID(0, 1.5, 0.02, 0.25, -1000, 1000)), rollPID(
				new PID(0, 2.0, 0.08, 0.25, -1000, 1000)), throttle(1150), targetThrottle(
				1150), throttleMotors { 1000, 1000, 1000, 1000 }, roll(0), pitch(
				0), isFlying(false) {
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
}

void FlyingState::doActivity() {
	MPU6050::getMPU6050Instance().update();

	if (!handleSerial()) {
		return;
	}

//	Serial.println(isFlying);
//
//	float rollMPU = MPU6050::getMPU6050Instance().getRoll();
//	float pitchMPU = MPU6050::getMPU6050Instance().getPitch();
//
//	if (isFlying) {
//		roll = rollPID->compute(rollMPU);
//		pitch = pitchPID->compute(pitchMPU);
//	}
////	else if (throttle < 1400 && throttle > 1390) {
////		reset();
////	}
//
//// 	Roll en Pitch debug lines
////	Serial.print("Roll:\t");
////	Serial.print(rollMPU);
////	Serial.print("\tError:\t");
////	Serial.print(rollPID->getError());
////	Serial.print("\tProportional:\t");
////	Serial.print(rollPID->getProportional());
////	Serial.print("\tIntegral:\t");
////	Serial.print(rollPID->getIntegral());
////	Serial.print("\tDerivative:\t");
////	Serial.print(rollPID->getDerivative());
////	Serial.print("\t,PID roll:\t");
////	Serial.print(roll);
////
////	Serial.print("\t\tPitch:\t");
////	Serial.print(pitchMPU);
////	Serial.print("\tError:\t");
////	Serial.print(pitchPID->getError());
////	Serial.print("\tProportional:\t");
////	Serial.print(pitchPID->getProportional());
////	Serial.print("\tIntegral:\t");
////	Serial.print(pitchPID->getIntegral());
////	Serial.print("\tDerivative:\t");
////	Serial.print(pitchPID->getDerivative());
////	Serial.print("\t,PID pitch:\t");
////	Serial.print(pitch);
//
//	if (targetThrottle > throttle) {
//		throttle += 2;
//	} else if (targetThrottle == 1000) {
//		throttle = 1000;
//	}
//
//	throttleMotors[0] = round(throttle + pitch + roll);
//	throttleMotors[1] = round(throttle + pitch - roll);
//	throttleMotors[2] = round(throttle - pitch - roll);
//	throttleMotors[3] = round(throttle - pitch + roll);
//
//	for (int i = 0; i < 4; i++) {
//		MotorController::getMotorControllerInstance().setMotorValue(i,
//				throttleMotors[i]);
//	}

//	Motor debug lines
//	Serial.print("\t\tMotor0:\t");
//	Serial.print(throttleMotors[0]);
//	Serial.print("\tMotor1:\t");
//	Serial.print(throttleMotors[1]);
//	Serial.print("\tmotor2:\t");
//	Serial.print(throttleMotors[2]);
//	Serial.print("\tMotor3:\t");
//	Serial.println(throttleMotors[3]);

//		this->run();

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
}

void FlyingState::setIsFlying(bool isFlying) {
	this->isFlying = isFlying;
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
