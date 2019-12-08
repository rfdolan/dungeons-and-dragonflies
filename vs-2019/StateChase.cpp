#include "StateChase.h"

#include "LogManager.h"
#include "Monster.h"

StateChase::StateChase() {

}

void StateChase::Enter(df::Object* p_obj) {
	
	//set chase sprite.
	p_obj->setSprite("monster-chase");
	p_obj->setSpeed(CHASE_SPEED);

	LM.writeLog("Statechase::Enter():Set monster-chase");
}

void StateChase::Execute(df::Object* p_obj) {

	//this state deals with a Monster, so case Object *.
	Monster* p_monster = dynamic_cast<Monster *>(p_obj);

	//move
	//implement chasing 
	p_monster->setDirection(p_monster->seeHero());
	p_monster->stopAnimation(false);

	//if cannots see hero, enter seek.
	if (p_monster->seeHero() == df::Vector(0, 0)) {
		df::StateMachine* p_machine = p_monster->getStateMachine();
		p_machine->changeState(p_monster->getStateSearch());
	}

}