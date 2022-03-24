/*
 * FlightController.cpp
 *
 *  Created on: 20 jan. 2022
 *      Author: Rens
 */

#include "states/IdleState.h"
#include "FlightController.h"
#include "MPU6050.h"
#include "MotorController.h"

FlightController::FlightController() :
		Context("FlightController") {
}

FlightController::~FlightController() {
}

void FlightController::setup() {
	MotorController::getMotorControllerInstance().initMotors();
	MPU6050::getMPU6050Instance().setup();

	setCurrentState(new IdleState(this));
}

void FlightController::run() {
	currentState->doActivity();
}
