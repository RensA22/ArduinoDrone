/*
 * FlightController.cpp
 *
 *  Created on: 20 jan. 2022
 *      Author: Rens
 */

#include <FlightController.h>
#include <Arduino.h>

FlightController::FlightController(const int _motorpins[4]) :
		currentState(state::idle), nMotors(4), mpu(new GY521(0x68)) {
	for (int i = 0; i < nMotors; i++) {
		motors[i] = new Motor(_motorpins[i]);
	}

}

void FlightController::setup() {
	Wire.begin();
	delay(100);
	while (mpu->wakeup() == false) {
		Serial.print(millis());
		Serial.println("\tCould not connect to GY521");
		delay(1000);
	}
	mpu->setAccelSensitivity(0);  // 8g
	mpu->setGyroSensitivity(0);   // 500 degrees/s

	mpu->setThrottle();

	// set calibration values from calibration sketch.
	mpu->axe = 0;
	mpu->aye = 0;
	mpu->aze = 0;
	mpu->gxe = 0;
	mpu->gye = 0;
	mpu->gze = 0;
}

void FlightController::run() {

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
	default:
		Serial.println("ERROR: State not recognized");
		return;
		break;
	}
}

void FlightController::hoverDrone() {
	float targetRPM = 80;
	mpu->read();

	float angleX = mpu->getAngleX();

	int motorLinks = round(targetRPM - (targetRPM * (angleX / 100)));
	int motorRechts = round(targetRPM + (targetRPM * (angleX / 100)));

	setMotorValue(0, motorLinks);
	setMotorValue(1, motorRechts);
	setMotorValue(2, motorRechts);
	setMotorValue(3, motorLinks);

	Serial.print("Angle: ");
	Serial.print(angleX);
	Serial.print(" ,L: ");
	Serial.print(motorLinks);
	Serial.print(" ,R: ");
	Serial.println(motorRechts);

}

void FlightController::startMotors() {
	setMotorsValue(motors[0]->getCurrentValue() + 1);

	if (motors[0]->getCurrentValue() == 180) {
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
