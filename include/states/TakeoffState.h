/*
 * TakeoffState.h
 *
 *  Created on: 10 feb. 2022
 *      Author: Rens
 */

#ifndef INCLUDE_STATES_TAKEOFFSTATE_H_
#define INCLUDE_STATES_TAKEOFFSTATE_H_

#include <states/AbstractState.h>
#include <states/FlyingState.h>
#include "Context.h"
#include "PID.h"
#include "../../lib/RangefinderDriver/HCSR04.h"

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
	float getAltitude() const;

private:
	PID *altitudePID;
	FlyingState *parentState;

	float altitude;

};

#endif /* INCLUDE_STATES_TAKEOFFSTATE_H_ */
