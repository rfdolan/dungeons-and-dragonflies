#pragma once

#include "Object.h"
#include "Vector.h"

#define HERO_HEIGHT 3
#define HERO_WIDTH 3

class AttackRange : public df::Object {

public: 
	//create an objecto of the indicated size 
	AttackRange(df::Vector hero_position);
};