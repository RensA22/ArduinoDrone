/*
 * AbstractState.h
 *
 */

#ifndef STATEPATTERN_ABSTRACTSTATE_H_
#define STATEPATTERN_ABSTRACTSTATE_H_

#include <Arduino.h>
class Context;
//forward declaration

class AbstractState {
public:
	AbstractState(Context *aContext, String _name) :
			myContext(aContext), name(_name) {
	}
	;
	virtual ~AbstractState() = default;
	virtual void entryActivity() = 0;
	virtual void doActivity() =0;
	virtual void exitActivity() = 0;

	const String& getName() const {
		return name;
	}

protected:
	Context *myContext;

private:
	String name;
};

#endif /* STATEPATTERN_ABSTRACTSTATE_H_ */
