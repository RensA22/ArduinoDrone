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
#include "states/StopState.h"

TakeoffState::TakeoffState(Context *_context) :
		AbstractState(_context, "Takeoff"), distSens(new HCSR04(2, 0)), altitudePID(
				new PID(50, 0.5, 0.3, 0.5, 0, 10)), pitchPID(
				new PID(0, 1.5, 0.02, 0.25, -1000, 1000)), rollPID(
				new PID(0, 2.0, 0.08, 0.25, -1000, 1000)), throttle(1000), targetThrottle(
				1000), throttleMotors { 1000, 1000, 1000, 1000 }, roll(0), pitch(
				0) {
//TakeOff height: 1530
}

TakeoffState::~TakeoffState() {
	delete distSens;
	delete altitudePID;
	delete pitchPID;
	delete rollPID;
}

void TakeoffState::entryActivity() {
}

void TakeoffState::doActivity() {
	MPU6050::getMPU6050Instance().update();

	if (SerialParser::getSerialParser().isMessageReady()) {
		String message = SerialParser::getSerialParser().getMessage();

		if (message == "reset") {
			Serial.println("************************************************");
			MPU6050::getMPU6050Instance().reset();
			rollPID->reset();
			pitchPID->reset();
			roll = 0;
			pitch = 0;

		} else if (message == "offset") {
			MPU6050::getMPU6050Instance().calculateOffset();
		} else if (message.toInt() != 0) {
			targetThrottle = message.toInt();

			Serial.print("Received: ");
			Serial.println(targetThrottle);
		}

		SerialParser::getSerialParser().clearBuffer();

	}

	float rollMPU = MPU6050::getMPU6050Instance().getRoll();
	float pitchMPU = MPU6050::getMPU6050Instance().getPitch();

	if (throttle >= 1400) {
		roll = rollPID->compute(rollMPU);
		pitch = pitchPID->compute(pitchMPU);
	} else if (throttle < 1400 && throttle > 1390) {
		Serial.println("************************************************");
		MPU6050::getMPU6050Instance().reset();
		rollPID->reset();
		pitchPID->reset();
		roll = 0;
		pitch = 0;
	}

	Serial.print("Roll:\t");
	Serial.print(rollMPU);
	Serial.print("\tError:\t");
	Serial.print(rollPID->getError());
	Serial.print("\tProportional:\t");
	Serial.print(rollPID->getProportional());
	Serial.print("\tIntegral:\t");
	Serial.print(rollPID->getIntegral());
	Serial.print("\tDerivative:\t");
	Serial.print(rollPID->getDerivative());
	Serial.print("\t,PID roll:\t");
	Serial.print(roll);

	Serial.print("\t\tPitch:\t");
	Serial.print(pitchMPU);
	Serial.print("\tError:\t");
	Serial.print(pitchPID->getError());
	Serial.print("\tProportional:\t");
	Serial.print(pitchPID->getProportional());
	Serial.print("\tIntegral:\t");
	Serial.print(pitchPID->getIntegral());
	Serial.print("\tDerivative:\t");
	Serial.print(pitchPID->getDerivative());
	Serial.print("\t,PID pitch:\t");
	Serial.print(pitch);

	if (targetThrottle > throttle) {
		throttle += 2;
	} else if (targetThrottle == 1000) {
		throttle = 1000;
	}

	throttleMotors[0] = round(throttle + pitch + roll);
	throttleMotors[1] = round(throttle + pitch - roll);
	throttleMotors[2] = round(throttle - pitch - roll);
	throttleMotors[3] = round(throttle - pitch + roll);

	for (int i = 0; i < 4; i++) {
		MotorController::getMotorControllerInstance().setMotorValue(i,
				throttleMotors[i]);
	}

	Serial.print("\t\tMotor0:\t");
	Serial.print(throttleMotors[0]);
	Serial.print("\tMotor1:\t");
	Serial.print(throttleMotors[1]);
	Serial.print("\tmotor2:\t");
	Serial.print(throttleMotors[2]);
	Serial.print("\tMotor3:\t");
	Serial.println(throttleMotors[3]);
}

void TakeoffState::exitActivity() {
}

float TakeoffState::calculateSetPoint(float angle, float throttle) {
	float level_adjust = angle * 15; // Value 15 limits maximum angle value to ±32.8°
	float set_point = 0;

	set_point -= level_adjust;
	set_point /= 3;

	return set_point;
}
