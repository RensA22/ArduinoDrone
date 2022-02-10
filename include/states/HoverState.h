/*
 * HoverState.h
 *
 *  Created on: 3 feb. 2022
 *      Author: Rens
 */

#ifndef INCLUDE_STATES_HOVERSTATE_H_
#define INCLUDE_STATES_HOVERSTATE_H_

#include <states/AbstractState.h>
#include "Context.h"
#include "PID.h"

class HoverState: public AbstractState {
public:
	HoverState(Context *_context);
	virtual ~HoverState();
	HoverState(const HoverState &other) = delete;
	HoverState(HoverState &&other) = delete;
	HoverState& operator=(const HoverState &other) = delete;

	void entryActivity();
	void doActivity();
	void exitActivity();
private:
	PID *rollPID;
	PID *pitchPID;
};

#endif /* INCLUDE_STATES_HOVERSTATE_H_ */
