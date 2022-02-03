/*
 * FlyingIdleState.cpp
 *
 *  Created on: 3 feb. 2022
 *      Author: Rens
 */

#include <states/FlyingIdleState.h>
#include <states/HoverState.h>
#include <Arduino.h>

#include "SerialParser.h"

FlyingIdleState::FlyingIdleState(Context *_context) :
		AbstractState(_context) {
}

void FlyingIdleState::entryActivity() {
	Serial.println("Entry flying idle");
}

void FlyingIdleState::doActivity() {
	if (SerialParser::getSerialParser().isMessageReady()) {
		String message = SerialParser::getSerialParser().getMessage();

		if (message == "hover") {
			myContext->setCurrentState(new HoverState(myContext));
		}
	}
}

void FlyingIdleState::exitActivity() {
}
