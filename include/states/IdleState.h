/*
 * IdleState.h
 *
 *  Created on: 2 feb. 2022
 *      Author: Rens
 */

#ifndef INCLUDE_STATES_IDLESTATE_H_
#define INCLUDE_STATES_IDLESTATE_H_

#include "AbstractState.h"

class IdleState: public AbstractState {
public:
	IdleState(Context *_context);
	virtual ~IdleState() = default;
	IdleState(const IdleState &other) = delete;
	IdleState(IdleState &&other) = delete;
	IdleState& operator=(const IdleState &other) = delete;

	void entryActivity();
	void doActivity();
	void exitActivity();
};

#endif /* INCLUDE_STATES_IDLESTATE_H_ */
