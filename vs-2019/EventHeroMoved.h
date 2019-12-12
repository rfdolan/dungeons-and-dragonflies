#pragma once

#include "Event.h"
#include "Hero.h"

const std::string HERO_MOVED_EVENT = "hero_moved";

class EventHeroMoved : public df::Event {
private:
	Hero* m_hero;
public:
	EventHeroMoved(Hero* p_hero);
	Hero* getHero();
	
};