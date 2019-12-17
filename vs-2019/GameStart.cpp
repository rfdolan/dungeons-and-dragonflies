
#include "Windows.h"

//engine 
#include "LogManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "Box.h"
#include "Pause.h"

//game
#include "GameStart.h"
#include "Hunger.h"
#include "FloorNum.h"
#include "Map.h"
#include "EventGameOver.h"
#include "GameOver.h"
#include "Hero.h"

GameStart::GameStart(){
	Hero* h = new Hero();
	m_p_hero = h;
	m_p_hero->setVisible(false);
	hasStarted = false;
	
	Map* m = new Map();
	m_map = m;
	m->setHero(m_p_hero);

	//df::Box b = WM.getView();
	//setPosition(b.getCorner());
	WM.setViewFollowing(this);

	setType("GameStart");

	//link to "message" sprite
	setSprite("gamestart");

	//put in center of screen 
	setLocation(df::CENTER_CENTER);

	//register for "keyboard" event 
	registerInterest(df::KEYBOARD_EVENT);

	//see if game is over =
	registerInterest(GAME_OVER_EVENT);

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

	if (p_e->getType() == GAME_OVER_EVENT) {
		new GameOver();
		df::Vector v(getPosition().getX(), getPosition().getY());
		df::Box b;
		b.setCorner(v);
		//WM.setViewFollowing(this);
	

		
		
		//new GameStart(m_p_hero);
		
	}
	return  0;
}

void GameStart::start() {
	
	
	
	m_p_hero->setVisible(true);


	//Hero* hero = new Hero();
	//m_p_hero = hero;

	//populate hunger
	new Hunger;
	new FloorNum;


	//Map* m = new Map();
	// Generate world.
	m_map->generateMap(m_p_hero);

	RM.getMusic("ambient-1")->play();
	setVisible(false);
}

// Override default draw so as not to display "value"
int GameStart::draw() {
	return df::Object::draw();
}
