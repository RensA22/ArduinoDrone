/*
 * FlightController.cpp
 *
 *  Created on: 20 jan. 2022
 *      Author: Rens
 */

#include <FlightController.h>
#include <Arduino.h>

FlightController::FlightController(const int _motorpins[4]) :
		currentState(state::idle), throttle(1200), nMotors(4), mpu(new MPU6050), altitudePID(
				new PID(30, 0.65, 0.3, 0.5, 0, 10)), rollPID(
				new PID(0, 0.05, 0.005, 0.02, -1000, 50)), distSens(
				new HCSR04(2, 0)) {
	for (int i = 0; i < nMotors; i++) {
		motors[i] = new Motor(_motorpins[i]);
	}
	//Give esc some time to startup.
	delay(5000);

}

void FlightController::setup() {
	mpu->setup();
}

void FlightController::run() {
	mpu->update();
//	short dist = distSens->measureDistance();
//	float out = 0;

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
//		out = altitudePID->compute(dist);
//		setMotorsValue (out);
//		Serial.print(" ,dist: ");
//		Serial.print(dist);
//		Serial.print(" ,pid: ");
//		Serial.println(out);
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
	float angleX = round(mpu->getAngleX());
	float out = rollPID->compute(angleX);

	int motorLinks = round(throttle - out);
	int motorRechts = round(throttle + out);

//	Serial.print(" pid: ");
//	Serial.println(out);
//
	setMotorValue(0, motorLinks);
	setMotorValue(1, motorRechts);
	setMotorValue(2, motorRechts);
	setMotorValue(3, motorLinks);

	Serial.print("Angle: ");
	Serial.print(angleX);
	Serial.print(" ,MotorLinks: ");
	Serial.print(motorLinks);
	Serial.print(" ,motorRechts: ");
	Serial.println(motorRechts);

}

void FlightController::startMotors() {
	setMotorsValue(1000);
//	setMotorsValue(motors[0]->getCurrentValue() + 10);

//	if (motors[0]->getCurrentValue() == motors[0]->getMaxValue()) {
//		Serial.println("Started motors. Go to idle state");
//		this->currentState = state::idle;
//	}
}

void FlightController::stopMotors() {
	setMotorsValue(motors[0]->getMinValue());
}

void FlightController::setCurrentState(state currentState) {
	this->currentState = currentState;
}

void FlightController::setMotorsValue(const uint16_t value) {
	for (int i = 0; i < nMotors; i++) {
		setMotorValue(i, value);
	}
}

void FlightController::setMotorValue(const unsigned char motorId,
		const uint16_t value) {
	motors[motorId]->writeMotorValue(value);
}
