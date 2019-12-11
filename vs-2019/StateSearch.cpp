#include "StateSearch.h"
#include "LogManager.h"
#include "Monster.h"

df::Vector StateSearch::chooseDirection()
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

StateSearch::StateSearch()
{
}

void StateSearch::Enter(df::Object* p_obj)
{
	// Set wander sprite.
	p_obj->setSprite("monster-walk");
	p_obj->setSpeed(SEARCH_SPEED);
	Monster* p_monster = dynamic_cast<Monster *>(p_obj);
	isThinking = false;
	p_monster->setMoveCountdown(MOVE_TIME_SEARCH);
	p_monster->setThinkCountdown(THINK_TIME_SEARCH);


	LM.writeLog("StateSearch::Enter():Set monster-walk");
}

void StateSearch::Execute(df::Object* p_obj)
{
	// This state deals with a Mummy
	Monster* p_monster = dynamic_cast<Monster *>(p_obj);

	// Move.
	// Implement searching (move faster and stop less frequently).
	// Start thinking.
	if (p_monster->getMoveCountdown() <= 0 && !isThinking) {
		//LM.writeLog("Start thinking");
		// Stop moving.
		p_monster->setSpeed(0);

		// Reset moving countdown.
		p_monster->setMoveCountdown(MOVE_TIME_SEARCH);
		isThinking = true;
	}

	// Start moving
	if (p_monster->getThinkCountdown() <= 0 && isThinking) {
	//	LM.writeLog("Start walking");
		// That's enough thinking, choose a direction and start moving.
		p_monster ->setDirection(chooseDirection());
		p_monster->setSpeed(SEARCH_SPEED);
		p_monster->stopAnimation(false);

		// Reset thinking countdown.
		p_monster->setThinkCountdown(THINK_TIME_SEARCH);
		isThinking = false;
	}
	// Decrement appropriate counter.
	if (isThinking) {
		p_monster->setThinkCountdown(p_monster->getThinkCountdown() - 1);
	}
	else {
		p_monster->setMoveCountdown(p_monster->getMoveCountdown() - 1);
	}


	// If we can see the hero, go into chase mode.
	if (!(p_monster->seeHero() == df::Vector(0, 0))) {
		df::StateMachine* p_machine = p_monster->getStateMachine();
		p_machine->changeState(p_monster->getStateChase());
		return;
	}
	// If we cannot sense the hero, go into wander mode
	if (!p_monster->senseHero()) {
		df::StateMachine* p_machine = p_monster->getStateMachine();
		p_machine->changeState(p_monster->getStateWander());
		return;
	}

}