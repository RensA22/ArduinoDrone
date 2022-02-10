/*
 * IdleState.cpp
 *
 *  Created on: 2 feb. 2022
 *      Author: Rens
 */

#include <states/IdleState.h>
#include <states/StartState.h>
#include "SerialParser.h"
#include "MPU6050.h"

IdleState::IdleState(Context *_context) :
		AbstractState(_context, "Idle") {
}

void IdleState::entryActivity() {
	MPU6050::getMPU6050Instance().reset();
}

void IdleState::doActivity() {
	if (SerialParser::getSerialParser().isMessageReady()) {
		String message = SerialParser::getSerialParser().getMessage();

		if (message == "start") {
			myContext->setCurrentState(new StartState(myContext));
			SerialParser::getSerialParser().clearBuffer();
		}
	}
}

void IdleState::exitActivity() {
}
