#pragma once
#ifndef HERO_H
#define HERO_H

#include "Object.h"
#include "EventKeyboard.h"
#include "EventCollision.h"
#include "AttackRange.h"

#define ATTACK_OBJ_LIFETIME 7

class Hero : public df::Object
{
public:
	Hero();
	int eventHandler(const df::Event* p_e);
	void stopAnimation(bool stop);
	bool isRunning;


private:
	bool walkSprite; //indicates which sprite we are on 
	AttackRange* m_attackObj;
	int m_attackObj_lifetime;
	bool isDead; 
	bool is_attacking;
	int attack_countdown;
	void kbd(const df::EventKeyboard* p_keyboard_event);
	void move(const df::EventKeyboard* p_keyboard_event);
	void run(const df::EventKeyboard* p_keyboard_event);
	void step();
	void col(const df::EventCollision* p_collision_event);

};

#endif;
