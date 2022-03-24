/*
 * FlyingIdleState.cpp
 *
 *  Created on: 3 feb. 2022
 *      Author: Rens
 */

#include <states/FlyingIdleState.h>
#include <states/TakeoffState.h>

#include "SerialParser.h"

FlyingIdleState::FlyingIdleState(Context *_context) :
		AbstractState(_context, "Flying idle") {
}

FlyingIdleState::~FlyingIdleState() {
}

void FlyingIdleState::entryActivity() {

}

void FlyingIdleState::doActivity() {
	if (SerialParser::getSerialParser().isMessageReady()) {
		String message = SerialParser::getSerialParser().getMessage();
		Serial.println(message);

		if (message == "takeoff") {
			myContext->setCurrentState(new TakeoffState(myContext));
			SerialParser::getSerialParser().clearBuffer();
		}
	}
}

void FlyingIdleState::exitActivity() {
}
