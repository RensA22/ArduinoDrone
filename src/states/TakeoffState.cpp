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
		AbstractState(_context, "Takeoff"), altitudePID(
				new PID(50, 2, 0.002, 0.1, -100, 50)), parentState(nullptr), altitude(
				0.0) {
//TakeOff height: 1530
}

TakeoffState::~TakeoffState() {
	delete altitudePID;
}

void TakeoffState::entryActivity() {
	reset();
	HCSR04::getHCSR04Instance().setup(2, 16);
	HCSR04::getHCSR04Instance().calcOffset();

	parentState = (FlyingState*) myContext;
	parentState->setTargetThrottle(1525);
}

void TakeoffState::doActivity() {
	if (SerialParser::getSerialParser().isMessageReady()) {
		String message = SerialParser::getSerialParser().getMessage();
	}

	altitude = HCSR04::getHCSR04Instance().measureDistance();

	float altPID = altitudePID->compute(altitude,
			(altitude < 50) ? true : false);

	Serial.print("Altitude:\t");
	Serial.print(altitude);
	Serial.print("\tAlt error:\t");
	Serial.print(altitudePID->getError());
	Serial.print("\tAlt Prop:\t");
	Serial.print(altitudePID->getProportional());
	Serial.print("\tAlt Integralk:\t");
	Serial.print(altitudePID->getIntegral());
	Serial.print("\tAlt Dervi:\t");
	Serial.print(altitudePID->getDerivative());
	Serial.print("\tAlt output:\t");
	Serial.print(altitudePID->getOutput());
	Serial.print("\tAltPID:\t");
	Serial.print(altPID);

	parentState->setAltThrottle(altPID);

}

void TakeoffState::exitActivity() {
//	delete parentState;
}

void TakeoffState::reset() {
}
