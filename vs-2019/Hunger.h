#pragma once

#include "Event.h"
#include "EventHeroMoved.h"
#include "ViewObject.h"

#define HUNGER_STRING "Hunger"

#define HIT_RATE 10
#define STEP_RATE 75
#define BIG_FOOD_VAL 10
#define FOOD_VAL 3
#define MONSTER_DAMAGE 3
#define FULL_COLOR df::Color::GREEN
#define HUNGRY_COLOR df::Color::YELLOW
#define STARVING_COLOR df::Color::RED

class Hunger : public df::ViewObject {
private:
	int hitDecreaseRate; //decrease rate for when player is hit 
	int moveDecreaseRate; //decrease rate for when player moves
	bool isDead;
	void step();
public:
	Hunger();
	int eventHandler(const df::Event* p_e);
	void playerHit();
	void playerMoved(EventHeroMoved *h);
};