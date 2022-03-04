/*
 * FlightController.cpp
 *
 *  Created on: 20 jan. 2022
 *      Author: Rens
 */

#include <Arduino.h>

#include "states/IdleState.h"
#include "FlightController.h"
#include "MPU6050.h"
#include "MotorController.h"

//#include "states/TakeoffState.h"

FlightController::FlightController() :
		Context("FlightController") {
}

void FlightController::setup() {
	setCurrentState(new IdleState(this));

//	MotorController::getMotorControllerInstance().initMotors();
}

void FlightController::run() {
	currentState->doActivity();
}
