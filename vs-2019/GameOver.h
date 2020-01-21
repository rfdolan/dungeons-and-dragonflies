#pragma once

#include "ViewObject.h"
#include "GameStart.h"
#include "Map.h"
#include "Hero.h"

class GameOver : public df::ViewObject {

private:
	int time_to_live;
	void step();

public:
	GameOver();
	~GameOver();
	int eventHandler(const df::Event* p_e);
	int draw();
};
