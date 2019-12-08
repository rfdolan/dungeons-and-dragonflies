
#pragma once

#ifndef MONSTER_H
#define MONSTER_H

//Engine 
#include "Event.h"
#include "Object.h"
#include "Vector.h"
#include "StateMachine.h"
#include "EventCollision.h"

//Game 
#include "game.h"
#include "Hero.h"
#include "StateWander.h"
#include "StateChase.h"
#include "StateSearch.h"



//set values 
#define WANDER_SPEED 0.35
#define MOVE_TIME_WANDER 60
#define THINK_TIME_WANDER 90
#define SEARCH_SPEED 0.15
#define SENSE_DISTANCE 12
#define CHASE_SPEED 0.20
#define TAKE_DAMAGE 2

class Monster : public df::Object {
private:
	Hero* m_p_hero;
	int m_move_countdown;
	int m_think_countdown;
	int m_damage_countdown;
	int health; 
	int currentSprite;


	df::StateMachine m_machine;
	StateWander m_state_wander;
	StateChase m_state_chase;
	StateSearch m_state_search;

public:
	Monster(Hero* p_hero);
	int eventHandler(const df::Event* e);
	Hero* getHero();
	void stopAnimation(bool stop);
	void hit(const df::EventCollision* p_collision_event);
	df::Vector seeHero();
	bool senseHero();
	int getMoveCountdown();
	void setMoveCountdown(int new_move_countdown);
	int getThinkCountdown();
	void setThinkCountdown(int new_think_countdown);
	StateWander *getStateWander();
	df::StateMachine* getStateMachine();
	StateChase* getStateChase();
	StateSearch* getStateSearch();

};

#endif;