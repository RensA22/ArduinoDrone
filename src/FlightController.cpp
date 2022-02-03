/*
 * FlightController.cpp
 *
 *  Created on: 20 jan. 2022
 *      Author: Rens
 */

#include "states/IdleState.h"
#include "states/StartState.h"
#include "states/StopState.h"

#include <FlightController.h>
#include <Arduino.h>
#include "SerialParser.h"

FlightController::FlightController() :
		Context(), altitudePID(new PID(30, 0.65, 0.3, 0.5, 0, 10)), rollPID(
				new PID(0, 0.05, 0.005, 0.02, -1000, 50)), distSens(
				new HCSR04(2, 0)) {
}

void FlightController::setup() {
	this->setCurrentState(new IdleState(this));
	MPU6050::getMPU6050Instance().setup();
}

void FlightController::run() {
	MPU6050::getMPU6050Instance().update();

	currentState->doActivity();
}
