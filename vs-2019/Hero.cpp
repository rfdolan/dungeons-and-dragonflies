// Engine includes
#include "EventKeyboard.h"
#include "EventStep.h"
#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"

// Game includes
#include "game.h"
#include "Hero.h"
#include "EventPlayerHit.h"
#include "EventHeroMoved.h"
#include "AttackRange.h"
#include "EventMonsterHit.h"


Hero::Hero()
{
	setType("Hero");
	setSprite("walk");
	stopAnimation(true);
	setSpeed(0);
	setAltitude(4);
	walkSprite = true;
	m_attackObj = NULL;
	m_attackObj_lifetime = ATTACK_OBJ_LIFETIME;

	// Need to control Hero with keyboard.
	registerInterest(df::KEYBOARD_EVENT);

	// Need to update move countdown each step.
	registerInterest(df::STEP_EVENT);

	//need to see if monster hit 
	registerInterest(PLAYER_HIT_EVENT);

	//reset attack obj if it hit monster 
	registerInterest(MONSTER_HIT_EVENT);
}

int Hero::eventHandler(const df::Event* p_e)
{
	LM.writeLog("GETTING EVENT");
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event = (const df::EventKeyboard*) p_e;
		kbd(p_keyboard_event);
		return 1;

	}
	if (p_e->getType() == df::STEP_EVENT) {
		//setSprite("walk");
		//stopAnimation(false);
		step();
		
		
		return 1;
	}
	if (p_e->getType() == PLAYER_HIT_EVENT) {
		//log 
		LM.writeLog("Hero was hit");
		
		//temporarly change color of hero 
		setSprite("hurt");
		walkSprite = false;
		//stopAnimation(false);

	}
	if (p_e->getType() == MONSTER_HIT_EVENT) {
		LM.writeLog("Player issued an efficient attack");
		
		//reset attack obj 
		m_attackObj->setSolidness(df::SPECTRAL);
		m_attackObj_lifetime = ATTACK_OBJ_LIFETIME;
	}
}

void Hero::stopAnimation(bool stop)
{
	df::Animation animation = getAnimation();
	if (stop) {
		if (animation.getSlowdownCount() != -1) {
			animation.setSlowdownCount(-1);
			animation.setIndex(0);
		}
	}
	else {
		if (animation.getSlowdownCount() == -1) {
			animation.setSlowdownCount(0);
			animation.setIndex(0);
		}
	}
	setAnimation(animation);


}

void Hero::kbd(const df::EventKeyboard* p_keyboard_event)
{
	LM.writeLog("KEYBOARD EVENT");
	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::Q:		 // Q to quit.
		GM.setGameOver();
		break;
	case df::Keyboard::A: //attack 
	case df::Keyboard::UPARROW:	 // up arrow
	case df::Keyboard::DOWNARROW:	 // down arrow
	case df::Keyboard::LEFTARROW:	 // left arrow
	case df::Keyboard::RIGHTARROW: // right arrow
		move(p_keyboard_event);
		break;
	default:
		break;
	};

	return;
}

// Movement code based off of movement code from pyramid game
void Hero::move(const df::EventKeyboard* p_keyboard_event)
{
	bool heroMoved = false; //did our hero move?

	LM.writeLog("Movin");
	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::UPARROW:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			df::Vector v(getVelocity().getX(), -HERO_SPEED.getY());
			setVelocity(v);
		}
		else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			df::Vector v(getVelocity().getX(), 0);
			setVelocity(v);
		}

		heroMoved = true;

		break;
	case df::Keyboard::DOWNARROW:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			df::Vector v(getVelocity().getX(), HERO_SPEED.getY());
			setVelocity(v);
		}
		else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			df::Vector v(getVelocity().getX(), 0);
			setVelocity(v);
		}

		heroMoved = true;

		break;
	case df::Keyboard::LEFTARROW:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			df::Vector v(-HERO_SPEED.getX(), getVelocity().getY());
			setVelocity(v);
		}
		else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			df::Vector v(0, getVelocity().getY());
			setVelocity(v);
		}

		heroMoved = true;
		break;
	case df::Keyboard::RIGHTARROW:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			df::Vector v(HERO_SPEED.getX(), getVelocity().getY());
			setVelocity(v);
		}
		else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			df::Vector v(0, getVelocity().getY());
			setVelocity(v);
		}
		heroMoved = true;

		break;
		
	case df::Keyboard::A:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			int x = getPosition().getX();
			int y = getPosition().getY();
			df::Vector v(x, y);
			m_attackObj = new AttackRange(v);
			m_attackObj_lifetime = ATTACK_OBJ_LIFETIME; //reset life
		}
		break;
		
	default:
		break;
	};

	// If not moving, stop animation.
	if (getSpeed() == 0)
		stopAnimation(true);
	else
		stopAnimation(false);

	//check if hunger needs to be decreased
	if (heroMoved) {

		//send a player moved event 
		EventHeroMoved heroMoved;
		WM.onEvent(&heroMoved);
	}
	return;
}

void Hero::step()
{
	
	//make sure we are in right sprite 
	if (!walkSprite) {
		setSprite("walk");
		walkSprite = true;
	}

	//check if time to delete attack obj
	if (m_attackObj != NULL) { //does it exist 
		m_attackObj_lifetime--; //decrease its life 
		
		if (m_attackObj_lifetime < 1) { //ready to die
			m_attackObj->setSolidness(df::SPECTRAL);
			m_attackObj_lifetime = ATTACK_OBJ_LIFETIME; //reset
		}
	}
}

