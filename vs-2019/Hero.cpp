// Engine includes
#include "EventKeyboard.h"
#include "EventStep.h"
#include "GameManager.h"
#include "LogManager.h"

// Game includes
#include "game.h"
#include "Hero.h"


Hero::Hero()
{
	setType("Hero");
	setSprite("walk");
	stopAnimation(true);
	setSpeed(0);
	setAltitude(4);
	// Need to control Hero with keyboard.
	registerInterest(df::KEYBOARD_EVENT);

	// Need to update move countdown each step.
	registerInterest(df::STEP_EVENT);

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
		step();
		return 1;
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
		break;
	default:
		break;
	};

	// If not moving, stop animation.
	if (getSpeed() == 0)
		stopAnimation(true);
	else
		stopAnimation(false);

	return;
}

void Hero::step()
{
	// Do step things
}

