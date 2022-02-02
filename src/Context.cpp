/*
 * Context.cpp
 *
 *  Created on: 2 feb. 2022
 *      Author: Rens
 */

#include <Context.h>

Context::Context() :
		currentState(nullptr) {

}

Context::~Context() {

	if (currentState != nullptr) {
		delete currentState;
	}
}

void Context::setCurrentState(AbstractState *newState) {
	if (this->currentState != nullptr) {
		delete this->currentState;
	}

	this->currentState = newState;
}
