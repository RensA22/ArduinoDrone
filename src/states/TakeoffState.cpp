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
				new PID(0, 1.3, 0.04, 1, -1000, 1000)), rollPID(
				new PID(0, 1.3, 0.04, 1, -1000, 1000)), throttle(1000), throttleMotors {
				1000, 1000, 1000, 1000 }, roll(0), pitch(0) {
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
			throttle = message.toInt();

			Serial.print("Received: ");
			Serial.println(throttle);
		}

		SerialParser::getSerialParser().clearBuffer();

	}

	float rollMPU = MPU6050::getMPU6050Instance().getRoll();
	float pitchMPU = MPU6050::getMPU6050Instance().getPitch();

	int safetyAngle = 15;

//	Serial.println(calculateSetPoint(rollMPU, throttle));

	if (rollMPU < -safetyAngle || rollMPU > safetyAngle
			|| pitchMPU < -safetyAngle || pitchMPU > safetyAngle) {
		MotorController::getMotorControllerInstance().stopMotors();
	} else {

		if (throttle >= 1350) {
			roll = rollPID->compute(rollMPU);
			pitch = pitchPID->compute(pitchMPU);
		}

		throttleMotors[0] = round(throttle + pitch + roll);
		throttleMotors[1] = round(throttle + pitch - roll);
		throttleMotors[2] = round(throttle - pitch - roll);
		throttleMotors[3] = round(throttle - pitch + roll);

		for (int i = 0; i < 4; i++) {
			MotorController::getMotorControllerInstance().setMotorValue(i,
					throttleMotors[i]);
		}

		Serial.print("AngleX:\t");
		Serial.print(rollMPU);
		Serial.print("\t,PID roll:\t");
		Serial.print(roll);
		Serial.print("\tAngleY:\t");
		Serial.print(pitchMPU);
		Serial.print("\tPID pitch:\t");
		Serial.print(pitch);
		Serial.print("\tMotor0:\t");
		Serial.print(throttleMotors[0]);
		Serial.print("\t,Motor1:\t");
		Serial.print(throttleMotors[1]);
		Serial.print("\t,motor2:\t");
		Serial.print(throttleMotors[2]);
		Serial.print("\t,Motor3:\t");
		Serial.println(throttleMotors[3]);
	}
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
