#pragma once

#include "State.h"

#define THINK_TIME_SEARCH 10 
#define MOVE_TIME_SEARCH 30 

class StateSearch : public df::State {

private :
	bool isThinking;
	df::Vector chooseDirection();

public: 
	StateSearch();

	void Enter(df::Object* p_obj);
	void Execute(df::Object* p_obj);
};