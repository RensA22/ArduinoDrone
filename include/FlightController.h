/*
 * FlightController.h
 *
 *  Created on: 20 jan. 2022
 *      Author: Rens
 */

#ifndef INCLUDE_FLIGHTCONTROLLER_H_
#define INCLUDE_FLIGHTCONTROLLER_H_

#include "Context.h"

class FlightController: public Context {
public:
	FlightController();
	virtual ~FlightController();
	FlightController(const FlightController &other) = delete;
	FlightController(FlightController &&other) = delete;

	/**
	 * This is the setup function where classes can be initialsed
	 * and the begin state is set. In this instance this is idleState.
	 */
	void setup();

	/**
	 *	This function runs the doactivity() of the currentState.
	 *	Nothing more and nothing less.
	 */
	void run();

};

#endif /* INCLUDE_FLIGHTCONTROLLER_H_ */
