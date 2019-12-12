
//engine 
#include "ResourceManager.h"
#include "GameManager.h"

//game
#include "GameStart.h"
#include "Hunger.h"
#include "FloorNum.h"
#include "Map.h"

GameStart::GameStart(Hero *p_hero){
	m_p_hero = p_hero;
	hasStarted = false;
	
	setType("GameStart");

	//link to "message" sprite
	setSprite("gamestart");

	//put in center of screen 
	setLocation(df::CENTER_CENTER);

	//register for "keyboard" event 
	registerInterest(df::KEYBOARD_EVENT);

	//play start music 
	//p_music = RM.getMusic("start-music");
	//playMusic();
}

//play start music 
void GameStart::playMusic() {
//	p_music->play();
}

//handle event 
int GameStart::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*) p_e;
		switch (p_keyboard_event->getKey()) {
		case df::Keyboard::P: 			// play
			if (!hasStarted) {
				if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
					start();
					hasStarted = true;
				}
			}	
			break;
		case df::Keyboard::Q:			// quit
			GM.setGameOver();
			break;
		default:
			break;
		}
		return 1;
	}
	return  0;
}

void GameStart::start() {
	
	m_p_hero->setVisible(true);

	//populate hunger
	new Hunger;
	new FloorNum;

	Map* m = new Map();
	// Generate world.
	m->generateMap(m_p_hero);

	RM.getMusic("ambient-1")->play();
	setVisible(false);
}

// Override default draw so as not to display "value"
int GameStart::draw() {
	return df::Object::draw();
}
