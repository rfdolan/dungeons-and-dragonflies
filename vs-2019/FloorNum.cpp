#include "FloorNum.h"
#include "EventStairs.h"
#include "EventGameOver.h"
#include "WorldManager.h"

FloorNum::FloorNum() {
	setLocation(df::TOP_RIGHT);
	setViewString(FLOOR_STRING);
	setColor(df::WHITE);
	setValue(1);
	setType("FloorNum");

	registerInterest(STAIRS_EVENT);
	registerInterest(GAME_OVER_EVENT);
}

int FloorNum::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == STAIRS_EVENT) {
		setValue(getValue() + 1);
		return 1;
	}
	if (p_e->getType() == GAME_OVER_EVENT) {
		//WM.markForDelete(this);
		return 1;
	}

	return 0;
}
