/*
 * FlyingState.cpp
 *
 *  Created on: 3 feb. 2022
 *      Author: Rens
 */

#include <states/FlyingState.h>
#include <states/FlyingIdleState.h>
#include <states/StopState.h>
#include <Arduino.h>

#include "Context.h"
#include "SerialParser.h"

FlyingState::FlyingState(Context *_context) :
		AbstractState(_context) {
}

void FlyingState::entryActivity() {
//	this->setCurrentState(new FlyingIdleState(this));
	Serial.println("Entry flying state");
}

void FlyingState::doActivity() {
	if (SerialParser::getSerialParser().isMessageReady()) {
		String message = SerialParser::getSerialParser().getMessage();

		if (message == "stop") {
			myContext->setCurrentState(new StopState(myContext));
		}
	}

//	this->run();
}

void FlyingState::exitActivity() {
}

//void FlyingState::run() {
//	this->currentState->doActivity();
//}

