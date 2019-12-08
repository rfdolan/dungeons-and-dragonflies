#pragma once

#include "Event.h"

const std::string MONSTER_HIT_EVENT = "monster_hit";

class EventMonsterHit : public df::Event {
public:
	EventMonsterHit();
};