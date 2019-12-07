#pragma once

#include "State.h"
#include "Object.h"



class StateWander : public df::State {
private:
	bool isThinking;
public: 
	StateWander();

	//change sprite to "walking Monster" 
	void Enter(df::Object* p_obj);

	//wander around level
	void Execute(df::Object* p_obj);
};