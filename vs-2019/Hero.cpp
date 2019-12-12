// Engine includes
#include "EventKeyboard.h"
#include "EventStep.h"
#include "EventCollision.h"
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
#include "EventStairs.h"
#include "EventGameOver.h"


Hero::Hero()
{
	setType("Hero");
	setSprite("walk");
	stopAnimation(true);
	setSpeed(0);
	setAltitude(4);
	setSolidness(df::HARD);
	walkSprite = true;
	m_attackObj = nullptr;
	m_attackObj_lifetime = ATTACK_OBJ_LIFETIME;

	isDead = false;

	isRunning = false;
	

	// Need to control Hero with keyboard.
	registerInterest(df::KEYBOARD_EVENT);

	// Need to update move countdown each step.
	registerInterest(df::STEP_EVENT);

	//need to see if monster hit 
	registerInterest(PLAYER_HIT_EVENT);

	//reset attack obj if it hit monster 
	registerInterest(MONSTER_HIT_EVENT);

	// Register interest in collisions for stairs
	registerInterest(df::COLLISION_EVENT);

	//check if game is over
	registerInterest(GAME_OVER_EVENT);
}

int Hero::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		if (!isDead) {
			const df::EventKeyboard* p_keyboard_event = (const df::EventKeyboard*) p_e;
			kbd(p_keyboard_event);
			
		}
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT) {
		//setSprite("walk");
		//stopAnimation(false);
		step();
		
		
		return 1;
	}
	if (p_e->getType() == PLAYER_HIT_EVENT) {
		if (!isDead) {
			//log 
			LM.writeLog("Hero was hit");

			//temporarly change color of hero 
			setSprite("hurt");
			walkSprite = false;
			//stopAnimation(false);
		}
		return 1;

	}
	if (p_e->getType() == MONSTER_HIT_EVENT) {
		if (!isDead) {
			LM.writeLog("Player issued an efficient attack");

			//reset attack obj 
			m_attackObj->setSolidness(df::SPECTRAL);
			m_attackObj_lifetime = ATTACK_OBJ_LIFETIME;
		}
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		if (!isDead) {
			const df::EventCollision* p_collision_event = (const df::EventCollision*) p_e;
			col(p_collision_event);
		}
		return 1;

	}
	

	//check if game over
	if (p_e->getType() == GAME_OVER_EVENT) {
		LM.writeLog("GAME IS OVER");
		
		//player is now dead
		isDead = true;

		//change sprite
		setSprite("dead2");

		setVelocity(df::Vector(0, 0));
	}
	return 0;
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
	//LM.writeLog("KEYBOARD EVENT");
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
	case df::Keyboard::SPACE:
		run(p_keyboard_event);
		break;
	default:
		break;
	};

	return;
}

void Hero::run(const df::EventKeyboard* p_keyboard_event) {
	if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
		df::Vector newVel = getVelocity();
		newVel.scale(2.0f);
		
		setVelocity(newVel);
		isRunning = true;
	}
	if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
		df::Vector newVel = getVelocity();
		newVel.scale(0.5f);
		
		setVelocity(newVel);
		isRunning = false;
	}
}

// Movement code based off of movement code from pyramid game
void Hero::move(const df::EventKeyboard* p_keyboard_event)
{
	bool heroMoved = false; //did our hero move?
	df::Vector currSpeed = HERO_SPEED;
	if (isRunning) {
		currSpeed = HERO_SPEED_RUN;
	}

	//LM.writeLog("Movin");
	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::UPARROW:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			df::Vector v(getVelocity().getX(), -currSpeed.getY());
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
			df::Vector v(getVelocity().getX(), currSpeed.getY());
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
			df::Vector v(-currSpeed.getX(), getVelocity().getY());
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
			df::Vector v(currSpeed.getX(), getVelocity().getY());
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
			if (m_attackObj_lifetime == ATTACK_OBJ_LIFETIME) {
				int x = getPosition().getX();
				int y = getPosition().getY();
				df::Vector v(x, y);
				m_attackObj = new AttackRange(v);
				//m_attackObj_lifetime = ATTACK_OBJ_LIFETIME; //reset life
			}
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
		EventHeroMoved heroMoved = EventHeroMoved(this);
		WM.onEvent(&heroMoved);
	}
	return;
}

void Hero::step()
{
	
	//make sure we are in right sprite 
	if (!walkSprite && !isDead) {
		setSprite("walk");
		walkSprite = true;
	}

	//check if time to delete attack obj
	if (m_attackObj != nullptr) {
		m_attackObj_lifetime--; //decrease its life 
	}
		
	if (m_attackObj_lifetime < 1 && m_attackObj != nullptr) { //ready to die
		WM.markForDelete(m_attackObj);
		m_attackObj = nullptr;
		//m_attackObj->setSolidness(df::SPECTRAL);
		m_attackObj_lifetime = ATTACK_OBJ_LIFETIME; //reset
	}
}

void Hero::col(const df::EventCollision* p_collision_event)
{
	if (p_collision_event->getObject1()->getType() == "Stairs" ||
		p_collision_event->getObject2()->getType() == "Stairs") {
		EventStairs stairs;
		WM.onEvent(&stairs);

	}
}

