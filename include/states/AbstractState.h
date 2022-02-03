/*
 * AbstractState.h
 *
 */

#ifndef STATEPATTERN_ABSTRACTSTATE_H_
#define STATEPATTERN_ABSTRACTSTATE_H_

class Context;
//forward declaration

class AbstractState {
public:
	AbstractState(Context *aContext) :
			myContext(aContext) {
	}
	;
	virtual ~AbstractState() = default;
	virtual void entryActivity() = 0;
	virtual void doActivity() =0;
	virtual void exitActivity() = 0;

protected:
	Context *myContext;
};

#endif /* STATEPATTERN_ABSTRACTSTATE_H_ */
