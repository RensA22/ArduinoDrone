/*
 * FlightController.cpp
 *
 *  Created on: 20 jan. 2022
 *      Author: Rens
 */

#include <FlightController.h>
#include <Arduino.h>

FlightController::FlightController(const int _motorpins[4]) :
		currentState(state::idle), nMotors(4), mpu(new MPU6050), altitudePID(
				new PID(30, 0.65, 0.3, 0.5, 0, 10)), rollPID(
				new PID(0, 1.3, 0.04, 18.0, -50, 50)), distSens(
				new HCSR04(2, 0)) {
	for (int i = 0; i < nMotors; i++) {
		motors[i] = new Motor(_motorpins[i]);
	}

}

void FlightController::setup() {
	mpu->setup();
}

void FlightController::run() {
	mpu->update();
	short dist = distSens->measureDistance();
	float out = 0;

	switch (currentState) {
	case idle:
		break;
	case start:
		startMotors();
		break;
	case stop:
		stopMotors();
		this->currentState = state::idle;
		break;
	case hover:
		hoverDrone();
		break;
	case pid_test:
		out = altitudePID->compute(dist);
		setMotorsValue(out);
		Serial.print(" ,dist: ");
		Serial.print(dist);
		Serial.print(" ,pid: ");
		Serial.println(out);
		break;
	default:
		Serial.println("ERROR: State not recognized");
		return;
		break;
	}
}

void FlightController::setMaxValue(int value) {
	altitudePID->setMaxValue(value);
}

void FlightController::hoverDrone() {
	float targetRPM = 80;

	float angleX = mpu->getAngleX();

//	int motorLinks = round(targetRPM - (targetRPM * (angleX / 100)));
//	int motorRechts = round(targetRPM + (targetRPM * (angleX / 100)));

	float out = rollPID->compute(angleX);
//	Serial.print(" pid: ");
//	Serial.println(out);
//
//	setMotorValue(0, motorLinks);
//	setMotorValue(1, motorRechts);
//	setMotorValue(2, motorRechts);
//	setMotorValue(3, motorLinks);

	Serial.print("Angle: ");
	Serial.print(angleX);
	Serial.print(" ,out: ");
	Serial.println(out);

}

void FlightController::startMotors() {
	setMotorsValue(motors[0]->getCurrentValue() + 1);

	if (motors[0]->getCurrentValue() == motors[0]->getMaxValue()) {
		this->currentState = state::idle;
	}
}

void FlightController::stopMotors() {
	setMotorsValue(0);
}

void FlightController::setCurrentState(state currentState) {
	this->currentState = currentState;
}

void FlightController::setMotorsValue(const char value) {
	for (int i = 0; i < nMotors; i++) {
		setMotorValue(i, value);
	}
}

void FlightController::setMotorValue(const unsigned char motorId,
		const char value) {
	motors[motorId]->writeMotorValue(value);
}
