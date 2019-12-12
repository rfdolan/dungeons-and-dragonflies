#pragma once

#include "Event.h"
#include "ViewObject.h"

#define HUNGER_STRING "Hunger"

#define HIT_RATE 10
#define STEP_RATE 50

class Hunger : public df::ViewObject {
private:
	int hitDecreaseRate; //decrease rate for when player is hit 
	int moveDecreaseRate; //decrease rate for when player moves
	bool isDead;
public:
	Hunger();
	int eventHandler(const df::Event* p_e);
	void playerHit();
	void playerMoved();
};