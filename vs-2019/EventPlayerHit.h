#pragma once

#include "Event.h"

const std::string PLAYER_HIT_EVENT = "player_hit";

class EventPlayerHit : public df::Event {
public: 
	EventPlayerHit();
};