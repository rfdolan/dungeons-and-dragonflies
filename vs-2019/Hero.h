#pragma once
#ifndef HERO_H
#define HERO_H

#include "Object.h"
#include "EventKeyboard.h"
class Hero : public df::Object
{
public:
	Hero();
	int eventHandler(const df::Event* p_e);
	void stopAnimation(bool stop);

private:
	void kbd(const df::EventKeyboard* p_keyboard_event);
	void move(const df::EventKeyboard* p_keyboard_event);
	void step();

};

#endif;
