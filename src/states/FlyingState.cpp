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
#include "MPU6050.h"

FlyingState::FlyingState(Context *_context) :
		AbstractState(_context, "Flying"), Context("Flying") {
}

FlyingState::~FlyingState() {
	delete this->currentState;
}

void FlyingState::entryActivity() {
	MPU6050::getMPU6050Instance().setup();
	this->setCurrentState(new FlyingIdleState(this));
}

void FlyingState::doActivity() {
	MPU6050::getMPU6050Instance().update();

	if (SerialParser::getSerialParser().isMessageReady()) {
		String message = SerialParser::getSerialParser().getMessage();

		if (message == "stop") {
			myContext->setCurrentState(new StopState(myContext));
			SerialParser::getSerialParser().clearBuffer();
		}
	}

	this->run();
}

void FlyingState::exitActivity() {
	if (this->currentState != nullptr) {
		this->currentState->exitActivity();
	}
}

void FlyingState::run() {

	this->currentState->doActivity();
}

