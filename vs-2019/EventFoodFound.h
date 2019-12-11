#pragma once

#include "Event.h"

const std::string FOOD_FOUND_EVENT = "food_found";

class EventFoodFound : public df::Event {
public: 
	EventFoodFound();
};