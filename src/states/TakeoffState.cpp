/*
 * TakeoffState.cpp
 *
 *  Created on: 10 feb. 2022
 *      Author: Rens
 */

#include <states/TakeoffState.h>
#include "SerialParser.h"
#include "MPU6050.h"
#include "MotorController.h"

TakeoffState::TakeoffState(Context *_context) :
		AbstractState(_context, "Takeoff"), distSens(new HCSR04(2, 0)), altitudePID(
				new PID(50, 0.5, 0.3, 0.5, 0, 10)), pitchPID(
				new PID(0, 0.05, 0.01, 0.02, -1000, 1000)), rollPID(
				new PID(0, 0.05, 0.005, 0.02, -1000, 1000)), throttle(1000), throttleMotors {
				1000, 1000, 1000, 1000 } {
//TakeOff height: 1530
}

TakeoffState::~TakeoffState() {
	delete distSens;
	delete altitudePID;
	delete pitchPID;
	delete rollPID;
}

void TakeoffState::entryActivity() {
	MotorController::getMotorControllerInstance().initMotors();
	MPU6050::getMPU6050Instance().setup();
}

void TakeoffState::doActivity() {
	MPU6050::getMPU6050Instance().update();

//	if (SerialParser::getSerialParser().isMessageReady()) {
//		String message = SerialParser::getSerialParser().getMessage();
//
//		if (message == "reset") {
//			MPU6050::getMPU6050Instance().reset();
//			rollPID->reset();
//			pitchPID->reset();
//
//		} else if (message.toInt() != 0) {
//			throttle = message.toInt();
//
//			Serial.print("Received: ");
//			Serial.println(throttle);
//		}
//
//		SerialParser::getSerialParser().clearBuffer();
//
//	}
//
//	float angleX = MPU6050::getMPU6050Instance().getAngleX();
//	float angleY = MPU6050::getMPU6050Instance().getAngleY();
//
//	float outRoll = rollPID->compute(angleX);
//	float outPitch = pitchPID->compute(angleY);
//
//	throttleMotors[0] = round(throttle - outPitch + outRoll);
//	throttleMotors[1] = round(throttle - outPitch - outRoll);
//	throttleMotors[2] = round(throttle + outPitch - outRoll);
//	throttleMotors[3] = round(throttle + outPitch + outRoll);
//
////	for (int i = 0; i < 4; i++) {
////		MotorController::getMotorControllerInstance().setMotorValue(i,
////				throttleMotors[i]);
////	}
//
//	Serial.print("AngleX: ");
//	Serial.print(angleX);
//	Serial.print(" ,PID roll: ");
//	Serial.println(outRoll);
//	Serial.print("		AngleY: ");
//	Serial.print(angleY);
//	Serial.print(" ,PID pitch: ");
//	Serial.print(outPitch);
//	Serial.print(" 		Motor0: ");
//	Serial.print(throttleMotors[0]);
//	Serial.print(" ,Motor1: ");
//	Serial.print(throttleMotors[1]);
//	Serial.print(" ,motor2: ");
//	Serial.print(throttleMotors[2]);
//	Serial.print(" ,Motor3: ");
//	Serial.println(throttleMotors[3]);

}

void TakeoffState::exitActivity() {
}
