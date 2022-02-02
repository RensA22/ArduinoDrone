/*
 * StartState.cpp
 *
 *  Created on: 2 feb. 2022
 *      Author: Rens
 */

#include <Arduino.h>
#include <states/StartState.h>
#include <states/IdleState.h>
#include "MotorController.h"

StartState::StartState(Context *_context) :
		AbstractState(_context) {
	Serial.println("Enterd Start state");
}

void StartState::doActivity() {
	if (MotorController::getMotorControllerInstance().startMotors()) {
//		myContext->setCurrentState(new IdleState(myContext));
	}
}
