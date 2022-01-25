/*
 * FlightController.h
 *
 *  Created on: 20 jan. 2022
 *      Author: Rens
 */

#ifndef INCLUDE_FLIGHTCONTROLLER_H_
#define INCLUDE_FLIGHTCONTROLLER_H_

#include "Motor.h"
//#include "MPU6050.h"
#include "GY521.h"

enum state {
	idle, start, stop, hover
};

class FlightController {
public:
	FlightController(const int _motorPins[4]);
	virtual ~FlightController() = default;
	FlightController() = delete;
	FlightController(const FlightController &other) = delete;
	FlightController(FlightController &&other) = delete;

	void setup();
	void run();
	void setCurrentState(state currentState);

private:
	state currentState;
	const char nMotors;
	GY521 *mpu;

	/* 0: Links onder
	 * 1: Rechts onder
	 * 2: Rechts boven
	 * 3: Links boven
	 */
	Motor *motors[4];

	void startMotors();
	void stopMotors();
	void hoverDrone();
	void setMotorsValue(const char value);
	void setMotorValue(const unsigned char motorId, const char value);

};

#endif /* INCLUDE_FLIGHTCONTROLLER_H_ */