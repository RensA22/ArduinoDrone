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
	Logger::getLoggerInstance().log(name + "\t~Context", INFO);

}

void Context::setCurrentState(AbstractState *newState) {
	if (this->currentState != nullptr) {
		Logger::getLoggerInstance().log(
				name + "\tExit:\t" + this->currentState->getName(), INFO);

		this->currentState->exitActivity();

		delete this->currentState;
	}

	this->currentState = newState;

	Logger::getLoggerInstance().log(
			name + "\tEntry:\t" + this->currentState->getName(), INFO);
	this->currentState->entryActivity();
}

const AbstractState* Context::getCurrentState() const {
	return currentState;
}
