#pragma once

#include "Event.h"

const std::string BIG_FOOD_EVENT = "big-food";

class EventBigFood : public df::Event {
public:
	EventBigFood();
};