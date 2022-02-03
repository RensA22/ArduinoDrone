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
#include "Context.h"

class FlightController: public Context {
public:
	FlightController();
	virtual ~FlightController() = default;
	FlightController(const FlightController &other) = delete;
	FlightController(FlightController &&other) = delete;

	void setup();
	void run();

private:
	PID *altitudePID;
	PID *rollPID;
	HCSR04 *distSens;

};

#endif /* INCLUDE_FLIGHTCONTROLLER_H_ */
