
#include "AttackRange.h"

AttackRange::AttackRange(df::Vector hero_position) {
	setType("AttackObj");
	
	//set object's position 
	setPosition(hero_position);

	//set object's sprite
	setSprite("attack_obj");
	
	//make it invisible
	setVisible(false);
	setSolidness(df::SOFT);

	//altitude 
	setAltitude(3);
}