#include "FloorNum.h"
#include "EventStairs.h"

FloorNum::FloorNum() {
	setLocation(df::TOP_RIGHT);
	setViewString(FLOOR_STRING);
	setColor(df::WHITE);
	setValue(1);

	registerInterest(STAIRS_EVENT);
}

int FloorNum::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == STAIRS_EVENT) {
		setValue(getValue() + 1);
		return 1;
	}
	return 0;
}
