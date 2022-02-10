/*
 * Context.cpp
 *
 *  Created on: 2 feb. 2022
 *      Author: Rens
 */

#include <Context.h>

Context::Context(String _name) :
		currentState(nullptr), name(_name) {
}

Context::~Context() {
	Serial.print(name);
	Serial.print("    ");
	Serial.println(" ~Context");
//	if (currentState != nullptr) {
//		Serial.print("~Context: ");
//		Serial.println(this->currentState->getName());
//		this->currentState->exitActivity();
//		delete currentState;
//	}
}

void Context::setCurrentState(AbstractState *newState) {
	if (this->currentState != nullptr) {
		Serial.print(name);
		Serial.print("    ");
		Serial.print("Exit: ");
		Serial.println(this->currentState->getName());

		this->currentState->exitActivity();

		delete this->currentState;
	}

	this->currentState = newState;

	Serial.print(name);
	Serial.print("    ");
	Serial.print("Entry: ");
	Serial.println(this->currentState->getName());
	this->currentState->entryActivity();
}
