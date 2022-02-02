/*
 * StopState.cpp
 *
 *  Created on: 2 feb. 2022
 *      Author: Rens
 */

#include <states/StopState.h>
#include <states/IdleState.h>
#include "MotorController.h"

StopState::StopState(Context *_context) :
		AbstractState(_context) {
	Serial.println("Enterd Stop state");

}

void StopState::doActivity() {
	MotorController::getMotorControllerInstance().stopMotors();
	myContext->setCurrentState(new IdleState(myContext));
}
