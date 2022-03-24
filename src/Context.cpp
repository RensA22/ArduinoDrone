/*
 * Context.cpp
 *
 *  Created on: 2 feb. 2022
 *      Author: Rens
 */

#include <Context.h>
#include "Logger.h"

Context::Context(String _name) :
		currentState(nullptr), name(_name) {
}

Context::~Context() {
	Logger::getLoggerInstance().log(name + "\t~Context");

//	if (currentState != nullptr) {
//		Serial.print("~Context: ");
//		Serial.println(this->currentState->getName());
//		this->currentState->exitActivity();
//		delete currentState;
//	}
}

void Context::setCurrentState(AbstractState *newState) {
	if (this->currentState != nullptr) {
		Logger::getLoggerInstance().log(
				name + "\tExit:\t" + this->currentState->getName());

		this->currentState->exitActivity();

		delete this->currentState;
	}

	this->currentState = newState;

	Logger::getLoggerInstance().log(
			name + "\tEntry:\t" + this->currentState->getName());
	this->currentState->entryActivity();
}

const AbstractState* Context::getCurrentState() const {
	return currentState;
}
