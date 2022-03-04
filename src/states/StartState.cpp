/*
 * StartState.cpp
 *
 *  Created on: 2 feb. 2022
 *      Author: Rens
 */

#include <Arduino.h>
#include <states/StartState.h>
#include <states/FlyingState.h>
#include <states/StopState.h>
#include "MotorController.h"
#include "SerialParser.h"

StartState::StartState(Context *_context) :
		AbstractState(_context, "Start") {
}

void StartState::entryActivity() {

}

void StartState::doActivity() {
	if (SerialParser::getSerialParser().isMessageReady()) {
		String message = SerialParser::getSerialParser().getMessage();

		if (message == "stop") {
			myContext->setCurrentState(new StopState(myContext));
			SerialParser::getSerialParser().clearBuffer();
		}
	} else if (MotorController::getMotorControllerInstance().startMotors()) {
		myContext->setCurrentState(new FlyingState(myContext));
	}
}

void StartState::exitActivity() {
}
