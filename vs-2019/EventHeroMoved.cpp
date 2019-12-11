
#include "EventHeroMoved.h"

EventHeroMoved::EventHeroMoved(Hero* p_hero) {
	setType(HERO_MOVED_EVENT);
	m_hero = p_hero;
	
}

Hero* EventHeroMoved::getHero()
{
	return m_hero;
}
