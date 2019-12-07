
//engine 
#include "LogManager.h"
//#include "StateMachine.h"

//game 
#include "Monster.h"
#include "StateWander.h"



df::Vector chooseDirection()
{
	int random = rand();
	if (random % 4 == 0) {
		return df::Vector(1, 0);
	}
	if (random % 4 == 1) {
		return df::Vector(-1, 0);
	}
	if (random % 4 == 2) {
		return df::Vector(0, 1);
	}
	if (random % 4 == 3) {
		return df::Vector(0, -1);
	}
}

StateWander::StateWander()
{

}

void StateWander::Enter(df::Object* p_obj)
{
	// Set wander sprite(white mummy).
	p_obj->setSprite("monster-walk");
	p_obj->setSpeed(0);
	Monster* p_monster = dynamic_cast<Monster *>(p_obj);
	p_monster->stopAnimation(true);
	isThinking = true;
	p_monster->setThinkCountdown(THINK_TIME_WANDER);
	p_monster->setMoveCountdown(MOVE_TIME_WANDER);

	LM.writeLog("StateWander::Enter():Set monster-walk");
}

void StateWander::Execute(df::Object* p_obj)
{
	//debugging 
	LM.writeLog("In StateWander Execute");

	// This state deals with a Monster
	Monster* p_monster = dynamic_cast<Monster *>(p_obj);

	// Start thinking.
	if (p_monster->getMoveCountdown() <= 0 && !isThinking) {
		LM.writeLog("Start thinking");
		// Stop moving.
		p_monster->setSpeed(0);
		p_monster->stopAnimation(true);
	
		// Reset moving countdown.
		p_monster->setMoveCountdown(MOVE_TIME_WANDER);
		isThinking = true;
	}

	// Start moving
	if (p_monster->getThinkCountdown() <= 0 && isThinking) {
		LM.writeLog("Start walking");
		// That's enough thinking, choose a direction and start moving.
		p_monster->setDirection(chooseDirection());
		p_monster->setSpeed(WANDER_SPEED);
		p_monster->stopAnimation(false);
		// Reset thinking countdown.
		p_monster->setThinkCountdown(THINK_TIME_WANDER);
		isThinking = false;
	}
	// Decrement appropriate counter.
	if (isThinking) {
		p_monster->setThinkCountdown(p_monster->getThinkCountdown() - 1);
	}
	else {
		p_monster->setMoveCountdown(p_monster->getMoveCountdown() - 1);
	}


	// If can sense Hero, enter seek state.
	if (p_monster->senseHero()) {
		df::StateMachine* p_machine = p_monster->getStateMachine();
		p_machine->changeState(p_monster->getStateSearch());
		return;
	}
}