#include "WorldManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "EventStep.h"
#include "AttackRange.h"

AttackRange::AttackRange(df::Vector hero_position) {
	setType("AttackObj");
	
	//set object's position 
	setPosition(hero_position);

	//set object's sprite
	setSprite("attack_obj");
	
	//make it invisible
	//setVisible(false);
	setSolidness(df::SOFT);

	//altitude 
	setAltitude(3);

	LM.writeLog("Created an attack range");
	registerInterest(df::STEP_EVENT);
	time_to_live = LIFETIME;
	active = true;
	RM.getSound("attack")->play();

}


int AttackRange::eventHandler(const df::Event* p_e)
{

	if (p_e->getType() == df::STEP_EVENT) {
		//setSprite("walk");
		//stopAnimation(false);
		time_to_live--;
		df::ObjectList allObjs = WM.getAllObjects();
		df::ObjectListIterator it = df::ObjectListIterator(&allObjs);
		for (it.first(); !it.isDone(); it.next()) {
			if (it.currentObject()->getType() == "Hero") {
				setPosition(it.currentObject()->getPosition());
			}

		}
		if (time_to_live < 0) {
			WM.markForDelete(this);
		}
		
		return 1;
	}
	return 0;
}

void AttackRange::deactivate()
{
	active = false;
}

bool AttackRange::isActive()
{
	return active;
}
