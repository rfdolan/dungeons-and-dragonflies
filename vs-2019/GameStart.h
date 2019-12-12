#pragma once

#include "Music.h"
#include "ViewObject.h"
#include "Hero.h"
#include "Map.h"


class GameStart : public df::ViewObject {
private: 
	//df::Music* p_music;
	void start();
	Hero* m_p_hero;
	bool hasStarted;
	Map* m_map;
public: 
	GameStart();
	int eventHandler(const df::Event* p_e);
	int draw();
	void playMusic();
};