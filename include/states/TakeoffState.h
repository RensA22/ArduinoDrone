/*
 * TakeoffState.h
 *
 *  Created on: 10 feb. 2022
 *      Author: Rens
 */

#ifndef INCLUDE_STATES_TAKEOFFSTATE_H_
#define INCLUDE_STATES_TAKEOFFSTATE_H_

#include <states/AbstractState.h>
#include "HCSR04.h"
#include "PID.h"

class TakeoffState: public AbstractState {
public:
	TakeoffState(Context *_context);
	virtual ~TakeoffState();
	TakeoffState(const TakeoffState &other) = delete;
	TakeoffState(TakeoffState &&other) = delete;
	TakeoffState& operator=(const TakeoffState &other) = delete;

	void entryActivity();
	void doActivity();
	void exitActivity();
	float calculateSetPoint(float angle, float throttle);
private:
	HCSR04 *distSens;
	PID *altitudePID;
	PID *pitchPID;
	PID *rollPID;

	uint16_t throttle;
	uint16_t throttleMotors[4];

	float roll;
	float pitch;
};

#endif /* INCLUDE_STATES_TAKEOFFSTATE_H_ */
