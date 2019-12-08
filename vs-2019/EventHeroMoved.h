#pragma once

#include "Event.h"

const std::string HERO_MOVED_EVENT = "hero_moved";

class EventHeroMoved : public df::Event {
public:
	EventHeroMoved();
};