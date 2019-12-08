#pragma once

#include "State.h"

class StateChase : public df::State {
public :
	StateChase();

	void Enter(df::Object* p_obj);
	void Execute(df::Object* p_obj);
};