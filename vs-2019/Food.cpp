//engine
#include "WorldManager.h"
#include "LogManager.h"

//game
#include "Food.h"
#include "EventFoodFound.h"
#include "EventBigFood.h"

//type 0 - small food, type 1- big food
//default - small food 
Food::Food(int type) {
	//set type number
	m_type = type;

	LM.writeLog("Food object created");

	//make soft
	setSolidness(df::SOFT);

	if (type == 1) { //big food 
		setSprite("big-food");
	}
	else { //small food 
		setSprite("food");
	}

	//set type 
	setType("Food");

	//interested in collisions
	registerInterest(df::COLLISION_EVENT);
}

//type 0 - small food, type 1- big food
//default - small food 
Food::Food(int type, df::Vector new_position) {
	//set type number
	m_type = type;

	LM.writeLog("Food object created");

	//set type 
	setType("Food");

	if (type == 1) { //big food 
		setSprite("big-food");
	}
	else { //small food 
		setSprite("food");
	}

	//set to specified position 
	setPosition(new_position);

	//make soft
	setSolidness(df::SOFT);

	//interested in collisions
	registerInterest(df::COLLISION_EVENT);
}

int Food::eventHandler(const df::Event* p_e) {

	//check collision
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		found(p_collision_event);
	}

	//return nothing if not a collision event 
	return 0;
}

void Food::found(const df::EventCollision* p_collision_event) {
	//want to know if hero found us
	if ((p_collision_event->getObject1()->getType()) == "Hero"){

		//create appropriate event
		if (m_type == 1) {  //big food 
			EventBigFood bigFood;
			WM.onEvent(&bigFood);
		}
		else { //small food
			//create food found event 
			EventFoodFound foodFound;
			WM.onEvent(&foodFound);
		}
		
		//delete itself
		WM.markForDelete(p_collision_event->getObject2());
	}

	//other hero case 
	//want to know if hero found us
	if ((p_collision_event->getObject2()->getType()) == "Hero") {

		//create appropriate event
		if (m_type == 1) {  //big food 
			EventBigFood bigFood;
			WM.onEvent(&bigFood);
		}
		else { //small food
			//create food found event 
			EventFoodFound foodFound;
			WM.onEvent(&foodFound);
		}

		//delete itself
		WM.markForDelete(p_collision_event->getObject1());
	}
}