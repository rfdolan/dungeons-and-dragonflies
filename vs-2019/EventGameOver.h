#pragma once

#include "Event.h"

const std::string GAME_OVER_EVENT = "game-over";

class EventGameOver : public df::Event {
public:
	EventGameOver();
};