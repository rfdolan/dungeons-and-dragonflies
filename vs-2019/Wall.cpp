#include "Wall.h"
#include "DisplayManager.h"
#include "LogManager.h"

Wall::Wall(int width, int height)
{
	//LM.writeLog("Creating wall");
	setType("Wall");
	setSolidness(df::HARD);

	m_width = width;
	m_height = height;
	df::Vector corner = df::Vector(-1 * m_width/2.0f, -1 * m_height/2.0f);
	df::Box box = df::Box(corner, (float)m_width, (float)m_height);
	setBox(box);
}

// Draw Wall centered at position.
int Wall::draw() {

	//LM.writeLog("hfdjkslhf:");
	df::Vector pos = getPosition();
	for (int y = -1 * m_height / 2; y <= m_height / 2; y++)
		for (int x = -1 * m_width / 2; x <= m_width / 2; x++) {
			pos.setX(getPosition().getX() + x);
			pos.setY(getPosition().getY() + y);
			DM.drawCh(pos, WALL_CHAR, WALL_COLOR);
		}

	return 0;
}
