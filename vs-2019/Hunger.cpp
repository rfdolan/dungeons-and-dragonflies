
//engine includes 
#include "Event.h"
#include "EventStep.h"
#include "LogManager.h"

//Game includes 
#include "Hunger.h"
#include "EventPlayerHit.h"
#include "EventHeroMoved.h"
#include "EventMonsterHit.h"
#include "EventFoodFound.h"
#include "EventBigFood.h"

Hunger::Hunger() {
	//view object	
	setLocation(df::TOP_LEFT);
	setViewString(HUNGER_STRING);
	setColor(df::WHITE);
	setValue(100);

	//decrease rate 
	hitDecreaseRate = HIT_RATE;
	moveDecreaseRate = STEP_RATE;

	//decrease hunger when player moves 
	registerInterest(HERO_MOVED_EVENT);

	//decrease hunger when hit by enemy 
	registerInterest(PLAYER_HIT_EVENT);

	//decrease hunger if monster was hit
	//(meaning player used attack)
	registerInterest(MONSTER_HIT_EVENT);

	//want to know if food was found
	registerInterest(FOOD_FOUND_EVENT);

	//want to know if big food was found 
	registerInterest(BIG_FOOD_EVENT);
}

//Handle event
int Hunger::eventHandler(const df::Event* p_e) {
	
	//decrease hunger when player is hit 
	if (p_e->getType() == PLAYER_HIT_EVENT) {
		playerHit();
		return 1;
	}

	//decrease hunger at a certain rate when player moves 
	if (p_e->getType() == HERO_MOVED_EVENT) {
		playerMoved();
		return 1;
	}

	//decrease hunger if hero uses attack 
	if (p_e->getType() == HERO_MOVED_EVENT) {
		setValue(getValue() - 5); //decrease by 1.
		return 1;
	}

	//increase hunger if hero finds small food
	if (p_e->getType() == FOOD_FOUND_EVENT) {
		setValue(getValue() + 3);
		return 1;
	}
	
	//increase hunger if hero finds big food 
	if (p_e->getType() == BIG_FOOD_EVENT) {
		setValue(getValue() + 10);
		return 1; 
	}

	//if get here, have ignored this event 
	return 0;
}

void Hunger::playerHit() {
	
	//check if it is time to decrease 
	if (hitDecreaseRate < 1) {
		setValue(getValue() - 5);
		hitDecreaseRate = HIT_RATE;  //reset hit decrease rate 
	}
	else {
		hitDecreaseRate--;
	}
}

void Hunger::playerMoved() {

	//check if it is time to decrease 
	if (moveDecreaseRate < 1) {
		setValue(getValue() - 1);
		moveDecreaseRate = STEP_RATE; //reset move decrease rate
	}
	else {
		moveDecreaseRate--;
	}
}