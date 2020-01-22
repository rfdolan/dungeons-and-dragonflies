#pragma once

#include "Object.h"
#include "Vector.h"

#define HERO_HEIGHT 3
#define HERO_WIDTH 3
#define LIFETIME 7

class AttackRange : public df::Object {

public: 
	//create an objecto of the indicated size 
	AttackRange(df::Vector hero_position);
	int eventHandler(const df::Event* p_e);
	void deactivate();
	bool isActive();
private:
	int time_to_live;
	bool active;
};