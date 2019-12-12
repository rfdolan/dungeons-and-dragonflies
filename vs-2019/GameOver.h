#pragma once

#include "ViewObject.h"
#include "GameStart.h"
#include "Map.h"
#include "Hero.h"

class GameOver : public df::ViewObject {

private:
	int time_to_live;
	void step();
	Map* m_map;
	Hero* m_p_hero;

public:
	GameOver( Map* m, Hero* hero);
	~GameOver();
	int eventHandler(const df::Event* p_e);
	int draw();
};
