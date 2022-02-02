/*
 * IdleState.cpp
 *
 *  Created on: 2 feb. 2022
 *      Author: Rens
 */

#include <states/IdleState.h>
#include <Arduino.h>

#include "MotorController.h"

IdleState::IdleState(Context *_context) :
		AbstractState(_context) {
	Serial.println("Enterd Idle state");
}

void IdleState::doActivity() {
}
