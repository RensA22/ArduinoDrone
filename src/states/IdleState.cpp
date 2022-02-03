/*
 * IdleState.cpp
 *
 *  Created on: 2 feb. 2022
 *      Author: Rens
 */

#include <states/IdleState.h>
#include <states/StartState.h>
#include "SerialParser.h"

IdleState::IdleState(Context *_context) :
		AbstractState(_context) {
}

void IdleState::entryActivity() {
	Serial.println("Entry Idle state");
}

void IdleState::doActivity() {
	if (SerialParser::getSerialParser().isMessageReady()) {
		String message = SerialParser::getSerialParser().getMessage();

		if (message == "start") {
			myContext->setCurrentState(new StartState(myContext));
		}
	}
}

void IdleState::exitActivity() {
}
