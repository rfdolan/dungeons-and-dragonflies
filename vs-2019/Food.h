#pragma once

#ifndef FOOD_H
#define FOOD_H

//engine 
#include "Event.h"
#include "Object.h"
#include "WorldManager.h"
#include "Vector.h"

//game 
#include "Hero.h"

class Food : public df::Object {
private: 
	int m_type;
public:
	Food(int type);
	Food(int type, df::Vector new_position);
	int eventHandler(const df::Event* e);
	void found(const df::EventCollision* p_collision_event);
};

#endif 
