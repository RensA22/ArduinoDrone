/*
 * FlightController.h
 *
 *  Created on: 20 jan. 2022
 *      Author: Rens
 */

#ifndef INCLUDE_FLIGHTCONTROLLER_H_
#define INCLUDE_FLIGHTCONTROLLER_H_

#include "Motor.h"
#include "MPU6050.h"
#include "PID.h"
#include "HCSR04.h"
#include "states/AbstractState.h"
#include "Context.h"

enum state {
	IDLE, START, STOP, HOVER
};

class FlightController: public Context {
public:
	FlightController();
	virtual ~FlightController() = default;
	FlightController(const FlightController &other) = delete;
	FlightController(FlightController &&other) = delete;

	void setup();
	void run();
//	void setCurrentState(AbstractState *newState);
	void setMaxValue(int val);

private:
//	AbstractState *currentState;
	MPU6050 *mpu;
	PID *altitudePID;
	PID *rollPID;
	HCSR04 *distSens;

	void hoverDrone();
	void handleSerialMessage();

};

#endif /* INCLUDE_FLIGHTCONTROLLER_H_ */
