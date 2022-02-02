/*
 * FlightController.cpp
 *
 *  Created on: 20 jan. 2022
 *      Author: Rens
 */

#include "states/IdleState.h"
#include "states/StartState.h"
#include "states/StopState.h"

#include <FlightController.h>
#include <Arduino.h>
#include "SerialParser.h"

FlightController::FlightController() :
		Context(), mpu(new MPU6050), altitudePID(
				new PID(30, 0.65, 0.3, 0.5, 0, 10)), rollPID(
				new PID(0, 0.05, 0.005, 0.02, -1000, 50)), distSens(
				new HCSR04(2, 0)) {
}

void FlightController::setup() {
	setCurrentState(new IdleState(this));
	mpu->setup();
}

void FlightController::run() {
	mpu->update();
	handleSerialMessage();

	currentState->doActivity();

////	short dist = distSens->measureDistance();
////	float out = 0;
//
//	handleSerialMessage();
//
//	switch (currentState) {
//	case IDLE:
//		break;
//	case START:
//		startMotors();
//		break;
//	case STOP:
//		stopMotors();
//		this->currentState = state::IDLE;
//		break;
//	case HOVER:
//		hoverDrone();
//		break;
//	default:
//		Serial.println("ERROR: State not recognized");
//		return;
//		break;
//	}
}

void FlightController::setMaxValue(int value) {
	altitudePID->setMaxValue(value);
}

void FlightController::hoverDrone() {
//	float angleX = round(mpu->getAngleX());
//	float out = rollPID->compute(angleX);
//
//	int motorLinks = round(throttle - out);
//	int motorRechts = round(throttle + out);
//
////	Serial.print(" pid: ");
////	Serial.println(out);
////
//	setMotorValue(0, motorLinks);
//	setMotorValue(1, motorRechts);
//	setMotorValue(2, motorRechts);
//	setMotorValue(3, motorLinks);
//
//	Serial.print("Angle: ");
//	Serial.print(angleX);
//	Serial.print(" ,MotorLinks: ");
//	Serial.print(motorLinks);
//	Serial.print(" ,motorRechts: ");
//	Serial.println(motorRechts);

}

void FlightController::handleSerialMessage() {
	if (SerialParser::getSerialParser().isMessageReady()) {
		String message = SerialParser::getSerialParser().getMessage();

		if (message == "start") {
			setCurrentState(new StartState(this));
		} else if (message == "stop") {
			setCurrentState(new StopState(this));
		}
//		else if (message == "hover") {
//			setCurrentState(state::HOVER);
//		} else if (message == "idle") {
//			setCurrentState(state::IDLE);
//		}
	}
}
