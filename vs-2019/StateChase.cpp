#include "StateChase.h"

#include "LogManager.h"
#include "Monster.h"

StateChase::StateChase() {

}

void StateChase::Enter(df::Object* p_obj) {
	
	//set chase sprite.
	p_obj->setSprite("monster-chase");
	//p_obj->setSpeed(CHASE_SPEED);

	LM.writeLog("Statechase::Enter():Set monster-chase");
}

void StateChase::Execute(df::Object* p_obj) {

	//this state deals with a Monster, so case Object *.
	Monster* p_monster = dynamic_cast<Monster *>(p_obj);

	//move
	//implement chasing 
	df::Vector direction = p_monster->seeHero();
	direction.normalize();
	direction.setX(direction.getX() * MONSTER_SPEED_CHASE.getX());
	direction.setY(direction.getY() * MONSTER_SPEED_CHASE.getY());

	p_monster->setVelocity(direction);
	p_monster->stopAnimation(false);

	//if cannots see hero, enter seek.
	if (p_monster->seeHero() == df::Vector(0, 0)) {
		df::StateMachine* p_machine = p_monster->getStateMachine();
		p_machine->changeState(p_monster->getStateSearch());
	}

}