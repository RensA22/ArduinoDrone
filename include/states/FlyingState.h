/*
 * statesFlyingState.h
 *
 *  Created on: 3 feb. 2022
 *      Author: Rens
 */

#ifndef INCLUDE_FLYINGSTATE_H_
#define INCLUDE_FLYINGSTATE_H_

#include "states/AbstractState.h"
#include "Context.h"
#include "PID.h"

class FlyingState: public AbstractState, public Context {
public:
	FlyingState(Context *_context);
	virtual ~FlyingState();
	FlyingState(const FlyingState &other) = delete;
	FlyingState(FlyingState &&other) = delete;
	FlyingState& operator=(const FlyingState &other) = delete;

	void entryActivity();
	void doActivity();
	void exitActivity();
	void run();

	void setIsFlying(bool isFlying);

private:
	PID *pitchPID;
	PID *rollPID;

	uint16_t throttle;
	uint16_t targetThrottle;
	uint16_t throttleMotors[4];

	float roll;
	float pitch;
	bool isFlying;

	/**
	 * Resets the PID and the values roll and pitch
	 */
	void reset();

	/**
	 * Handles the serial communication message if a message is received.
	 * Returns false when stop message is received. This is so that the class can destruct correctly.
	 * Else returns true.
	 * @return bool
	 */
	bool handleSerial();
};

#endif /* INCLUDE_FLYINGSTATE_H_ */
