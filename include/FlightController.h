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

	void setup();
	void run();

};

#endif /* INCLUDE_FLIGHTCONTROLLER_H_ */
