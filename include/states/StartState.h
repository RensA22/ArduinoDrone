/*
 * StartState.h
 *
 *  Created on: 2 feb. 2022
 *      Author: Rens
 */

#ifndef INCLUDE_STATES_STARTSTATE_H_
#define INCLUDE_STATES_STARTSTATE_H_

#include <states/AbstractState.h>
#include "Context.h"

class StartState: public AbstractState {
public:
	StartState(Context *_context);
	virtual ~StartState() = default;
	StartState(const StartState &other) = delete;
	StartState(StartState &&other) = delete;
	StartState& operator=(const StartState &other) = delete;

	void doActivity();
};

#endif /* INCLUDE_STATES_STARTSTATE_H_ */
