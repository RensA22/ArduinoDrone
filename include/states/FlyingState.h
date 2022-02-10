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

};

#endif /* INCLUDE_FLYINGSTATE_H_ */
