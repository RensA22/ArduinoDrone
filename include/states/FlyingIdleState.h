/*
 * FlyingIdleState.h
 *
 *  Created on: 3 feb. 2022
 *      Author: Rens
 */

#ifndef INCLUDE_STATES_FLYINGIDLESTATE_H_
#define INCLUDE_STATES_FLYINGIDLESTATE_H_

#include <states/AbstractState.h>

class FlyingIdleState: public AbstractState {
public:
	FlyingIdleState(Context *_context);
	virtual ~FlyingIdleState() = default;
	FlyingIdleState(const FlyingIdleState &other) = delete;
	FlyingIdleState(FlyingIdleState &&other) = delete;
	FlyingIdleState& operator=(const FlyingIdleState &other) = delete;

	void entryActivity();
	void doActivity();
	void exitActivity();
};

#endif /* INCLUDE_STATES_FLYINGIDLESTATE_H_ */
