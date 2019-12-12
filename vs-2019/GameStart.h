#pragma once

#include "Music.h"
#include "ViewObject.h"
#include "Hero.h"

class GameStart : public df::ViewObject {
private: 
	//df::Music* p_music;
	void start();
	Hero* m_p_hero;
	bool hasStarted;
public: 
	GameStart(Hero* p_hero);
	int eventHandler(const df::Event* p_e);
	int draw();
	void playMusic();
};