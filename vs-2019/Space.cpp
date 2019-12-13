#include "Space.h"
#include "game.h"
#include "Wall.h"
#include "LogManager.h"
#include "WorldManager.h"


Space::Space()
{
	
}

Space::~Space()
{
	deleteWalls();
}

Space::Space(df::Vector new_pos, PieceType type)
{
	m_piece_type = type;
	map_pos = new_pos;

	Relationship r1 = Relationship(df::Vector(map_pos.getX() - 1, map_pos.getY()));
	addRelationship(r1);
	Relationship r2 = Relationship(df::Vector(map_pos.getX() + 1, map_pos.getY()));
	addRelationship(r2);
	Relationship r3 = Relationship(df::Vector(map_pos.getX(), map_pos.getY() - 1));
	addRelationship(r3);
	Relationship r4 = Relationship(df::Vector(map_pos.getX(), map_pos.getY() + 1));
	addRelationship(r4);
}

void Space::setPieceType(PieceType type)
{
	m_piece_type = type;
}

PieceType Space::getPieceType() const
{
	return m_piece_type;
}

void Space::setRelationships(std::vector<Relationship> r)
{
	m_relationships = r;
}

std::vector<Relationship> Space::getRelationships() const
{
	return m_relationships;
}

int Space::addRelationship(Relationship r)
{
	std::vector<Relationship>::iterator it;
	std::vector<Relationship> ships = getRelationships();

	// If there is already a relationship at this space, remove it
	for (it = ships.begin(); it < ships.end(); ) {
		if (it->getPos() == r.getPos()) {
			it = ships.erase(it);
		}
		else {
			it++;
		}
	}
	// add this relationship to the array.
	ships.push_back(r);
	setRelationships(ships);
	return 0;
}

int Space::connect(df::Vector pos)
{
	Relationship r = Relationship(pos);
	r.setConnected(true);

	addRelationship(r);

	return 1;

}

void Space::setMapPos(df::Vector pos)
{
	map_pos = pos;
}

df::Vector Space::getMapPos() const
{
	return map_pos;
}

void Space::createInWorld()
{
	switch (getPieceType()) {
	case ROOM:
		createRoomInWorld();
		break;
	case HALLWAY:
		createHallwayInWorld();
		break;
	}

}

std::vector<Wall*> Space::getWalls()
{
	return m_walls;
}

void Space::deleteWalls()
{
	//LM.writeLog("Deleting walls!!!!!!!!!!!!!!!!!!!!!");
	for (int i = 0; i < m_walls.size(); i++) {
		WM.markForDelete(m_walls[i]);
	}

	
	//LM.writeLog("Deleted");

	
}

void Space::addWall(Wall* p_wall)
{
	m_walls.push_back(p_wall);
}

void Space::createRoomInWorld()
{
	int x_source = getMapPos().getX() *ROOM_WIDTH;
	int y_source = getMapPos().getY() * ROOM_HEIGHT;
	for (Relationship r : getRelationships()) {
		int x_diff = r.getPos().getX() - getMapPos().getX();
		int y_diff = r.getPos().getY() - getMapPos().getY();
		if (r.isConnected()) {
			// Create connected wall
			//LM.writeLog("Creating an opening wall");
			float x_pos1 = (x_source + (ROOM_WIDTH / 2.0f) + (y_diff * (5.0f * ROOM_WIDTH / 16.0f)) + (x_diff * ROOM_WIDTH/2.0f));
			float y_pos1 = (y_source + (ROOM_HEIGHT / 2.0f) + (x_diff * (5.0f * ROOM_HEIGHT / 16.0f)) + (y_diff * ROOM_HEIGHT/2.0f));
			float x_pos2 = (x_source + (ROOM_WIDTH / 2.0f) - (y_diff * (5.0f * ROOM_WIDTH / 16.0f)) + (x_diff * ROOM_WIDTH / 2.0f));
			float y_pos2 = (y_source + (ROOM_HEIGHT / 2.0f) - (x_diff * (5.0 * ROOM_HEIGHT / 16.0f)) + (y_diff * ROOM_HEIGHT / 2.0f));

			Wall* p_wall;
			p_wall = new Wall((abs(y_diff) * ROOM_WIDTH)/3.0f, (abs(x_diff) * ROOM_HEIGHT)/3.0f);
			p_wall->setPosition(df::Vector(x_pos1,y_pos1));
			addWall(p_wall);
			Wall* p_wall2;
			p_wall2 = new Wall((abs(y_diff) * ROOM_WIDTH)/3.0f, (abs(x_diff) * ROOM_HEIGHT)/3.0f);
			p_wall2->setPosition(df::Vector(x_pos2,y_pos2));
			addWall(p_wall2);

		}
		else {
			//LM.writeLog("Creating a solid wall");
			int x_pos = (x_source + (ROOM_WIDTH / 2.0f)) + (x_diff * (ROOM_WIDTH / 2.0f));
			int y_pos = (y_source + (ROOM_HEIGHT / 2.0f)) + (y_diff * (ROOM_HEIGHT / 2.0f));
			Wall* p_wall;
			p_wall = new Wall(abs(y_diff) * ROOM_WIDTH, abs(x_diff) * ROOM_HEIGHT);
			p_wall->setPosition(df::Vector(x_pos,y_pos));
			addWall(p_wall);
			//LM.writeLog("Wall created at %d, %d", x_pos, y_pos);

		}


	}
	//LM.writeLog("Room created");

}

void Space::createHallwayInWorld()
{
	int x_source = getMapPos().getX() *ROOM_WIDTH;
	int y_source = getMapPos().getY() * ROOM_HEIGHT;
	for (Relationship r : getRelationships()) {
		int x_diff = r.getPos().getX() - getMapPos().getX();
		int y_diff = r.getPos().getY() - getMapPos().getY();
		if (r.isConnected()) {
			//LM.writeLog("Creating an opening hall");
			float x_pos1 = (x_source + (ROOM_WIDTH/2.0f) + (x_diff * (5.0f * ROOM_WIDTH / 16.0f)) + (y_diff * (ROOM_WIDTH / 8.0f)));
			float y_pos1 = (y_source + (ROOM_HEIGHT/2.0f) + (y_diff * (5.0f * ROOM_HEIGHT / 16.0f)) + (x_diff * (ROOM_HEIGHT / 8.0f)));
			float x_pos2 = (x_source + (ROOM_WIDTH/2.0f) + (x_diff * (5.0f * ROOM_WIDTH / 16.0f)) - (y_diff * (ROOM_WIDTH / 8.0f)));
			float y_pos2 = (y_source + (ROOM_HEIGHT/2.0f) + (y_diff * (5.0f * ROOM_HEIGHT / 16.0f)) - (x_diff * (ROOM_HEIGHT / 8.0f)));

			Wall* p_wall;
			p_wall = new Wall(abs(x_diff) * (3.0 * ROOM_WIDTH/8.0f), abs(y_diff) * (3.0 * ROOM_HEIGHT/8.0f));
			p_wall->setPosition(df::Vector(x_pos1, y_pos1));
			addWall(p_wall);
			Wall* p_wall2;
			p_wall2 = new Wall(abs(x_diff) * (3.0 * ROOM_WIDTH/8.0f), abs(y_diff) * (3.0 * ROOM_HEIGHT/8.0f));
			p_wall2->setPosition(df::Vector(x_pos2, y_pos2));
			addWall(p_wall2);
		}
		else {
			//LM.writeLog("Creating a solid hall");
			int x_pos = (x_source + (ROOM_WIDTH / 2.0f) + (x_diff *(ROOM_WIDTH / 8.0f)));
			int y_pos = (y_source + (ROOM_HEIGHT / 2.0f) + (y_diff *(ROOM_HEIGHT / 8.0f)));
			Wall* p_wall;
			p_wall = new Wall(abs(y_diff) * (ROOM_WIDTH/4.0f), abs(x_diff) * (ROOM_HEIGHT/4.0f));
			p_wall->setPosition(df::Vector(x_pos,y_pos));
			addWall(p_wall);
		}
	}
	
}
