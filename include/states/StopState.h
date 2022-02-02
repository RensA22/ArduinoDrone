/*
 * StopState.h
 *
 *  Created on: 2 feb. 2022
 *      Author: Rens
 */

#ifndef INCLUDE_STATES_STOPSTATE_H_
#define INCLUDE_STATES_STOPSTATE_H_

#include "AbstractState.h"
#include "Context.h"

class StopState: public AbstractState {
public:
	StopState(Context *_context);
	virtual ~StopState() = default;
	StopState(const StopState &other) = delete;
	StopState(StopState &&other) = delete;
	StopState& operator=(const StopState &other) = delete;

	void doActivity();
};

#endif /* INCLUDE_STATES_STOPSTATE_H_ */
