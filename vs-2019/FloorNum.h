#pragma once
#include "ViewObject.h"
#include "Event.h"

#define FLOOR_STRING "FLOOR"
class FloorNum : public df::ViewObject
{
public:
	FloorNum();
	int eventHandler(const df::Event* p_e);
};

