/*
 * Context.h
 *
 *  Created on: 2 feb. 2022
 *      Author: Rens
 */

#ifndef INCLUDE_CONTEXT_H_
#define INCLUDE_CONTEXT_H_

#include "states/AbstractState.h"

class Context {
public:
	Context();
	virtual ~Context();
	Context(const Context &other) = delete;
	Context(Context &&other) = delete;
	Context& operator=(const Context &other) = delete;

	virtual void run() =0;

	void setCurrentState(AbstractState *newState);

protected:
	AbstractState *currentState;
};

#endif /* INCLUDE_CONTEXT_H_ */
