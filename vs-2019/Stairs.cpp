#include "Stairs.h"
#include "LogManager.h"

Stairs::Stairs()
{
	setType("Stairs");

	setSprite("stairs");
}

Stairs::Stairs(df::Vector new_position)
{
	setType("Stairs");
	setSprite("stairs");
	setPosition(new_position);
	LM.writeLog("Made a stairs.");
}
