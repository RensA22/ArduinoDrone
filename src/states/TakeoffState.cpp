/*
 * TakeoffState.cpp
 *
 *  Created on: 10 feb. 2022
 *      Author: Rens
 */

#include <states/TakeoffState.h>
#include <states/FlyingState.h>
#include "SerialParser.h"
#include "MPU6050.h"
#include "MotorController.h"
#include "states/StopState.h"

TakeoffState::TakeoffState(Context *_context) :
		AbstractState(_context, "Takeoff"), distSens(new HCSR04(2, 0)), altitudePID(
				new PID(50, 0.5, 0.3, 0.5, 0, 10)) {
//TakeOff height: 1530
}

TakeoffState::~TakeoffState() {
	delete distSens;
	delete altitudePID;

}

void TakeoffState::entryActivity() {
	reset();
}

void TakeoffState::doActivity() {

	if (SerialParser::getSerialParser().isMessageReady()) {
		String message = SerialParser::getSerialParser().getMessage();

//		if (message.toInt() != 0) {
//			targetThrottle = message.toInt();
//
//			Serial.print("Received: ");
//			Serial.println(targetThrottle);
//			SerialParser::getSerialParser().clearBuffer();
//		}

	}
//
//	FlyingState *fs = (FlyingState*) myContext;
//	fs->setIsFlying(true);

}

void TakeoffState::exitActivity() {
}

void TakeoffState::reset() {
}
