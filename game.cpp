//
// game.cpp
// 

// System includes
#include <stdlib.h>

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes
#include "vs-2019\Hero.h"
#include "vs-2019\Map.h"
#include "vs-2019\Space.h"
#include "vs-2019\Relationship.h"
#include "vs-2019\game.h"
#include "vs-2019\Wall.h"
#include "vs-2019\Stairs.h"
#include "vs-2019\Monster.h"
#include "vs-2019\Hunger.h"

//functions
void loadResources();
void populateWorld();
void createMap(Hero* p_hero);
df::Vector generateMove(Map* m, df::Vector curr_pos) ;
void createTestDungeon();
bool placeStairs(Map* m, df::Vector start_pos);
void placeObject(df::Object* p_o);


int main(void) {
	srand((unsigned int)time(NULL));

	// Start up game manager.
	if (GM.startUp()) {
		LM.writeLog("Error starting game manager!");
		GM.shutDown();
		return 0;
	}

	// Set flush of logfile during development (when done, make false).
	LM.setFlush(true);

	// Show splash screen.
	//df::splash();

	loadResources();

	populateWorld();

	LM.writeLog("About to run");
	GM.run();
	// Shut everything down.
	GM.shutDown();
}

void loadResources() {
	//hero sprites
	RM.loadSprite("sprites/hero-walk-spr.txt", "walk");
	RM.loadSprite("sprites/stairs-spr.txt", "stairs");
	RM.loadSprite("sprites/hero_hurt-spr.txt", "hurt");
	RM.loadSprite("sprites/hero-attack-spr.txt", "attack");

	//monster sprites
	RM.loadSprite("sprites/monster-walk-spr.txt", "monster-walk");
	RM.loadSprite("sprites/monster-chase-spr.txt", "monster-chase");
	RM.loadSprite("sprites/monster-hurt01-spr.txt", "monster-hurt1");
	RM.loadSprite("sprites/monster-hurt02-spr.txt", "monster-hurt2");
	RM.loadSprite("sprites/monster-hurt03-spr.txt", "monster-hurt3");

	//attack object
	RM.loadSprite("sprites/attack-obj-spr.txt", "attack_obj");
}

void populateWorld() {

	WM.setBoundary(df::Box(df::Vector(0, 0), (ROOM_WIDTH * MAP_WIDTH) + 1, (ROOM_HEIGHT * MAP_HEIGHT) + 1));
	float X = WM.getBoundary().getHorizontal();
	float Y = WM.getBoundary().getVertical();

	Hero* p_hero = new Hero;

	
	//populate hunger
	new Hunger;

	// Generate world.
	createMap(p_hero);
}

void createTestDungeon() {
	Map* m = new Map();
	Space s1 = Space(df::Vector(0, 0), ROOM);
	//s1.connect(df::Vector(1, 0));
	//s1.connect(df::Vector(0, 1));
	Space s2 = Space(df::Vector(1, 0), HALLWAY);
	//s2.connect(df::Vector(0, 0));
	//s2.connect(df::Vector(2, 0));
	Space s3 = Space(df::Vector(2, 0), ROOM);
	//s3.connect(df::Vector(1, 0));
	Space s4 = Space(df::Vector(0, 1), ROOM);
	//s4.connect(df::Vector(0, 0));
	Space s5 = Space(df::Vector(1, 1), HALLWAY);


	m->addSpace(s1);
	m->addSpace(s2);
	m->addSpace(s3);
	m->addSpace(s4);
	m->addSpace(s5);
	m->connectSpacesAt(df::Vector(0, 0), df::Vector(1, 0));
	m->connectSpacesAt(df::Vector(0, 0), df::Vector(0, 1));
	m->connectSpacesAt(df::Vector(1, 0), df::Vector(2, 0));
	m->connectSpacesAt(df::Vector(1, 0), df::Vector(1, 1));
	m->connectSpacesAt(df::Vector(1, 1), df::Vector(0, 1));
	//m->connectSpacesAt(df::Vector(0, 0), df::Vector(0, 1));
	//m->connectSpacesAt(df::Vector(0, 1), df::Vector(1, 1));
	//m->connectSpacesAt(df::Vector(1, 0), df::Vector(2, 0));
	m->create();

}

void createMap(Hero *p_hero) {
	//createTestDungeon();
	Map* m = new Map();

	// Create start.
	int startX = rand() % MAP_WIDTH;
	int startY = rand() % MAP_HEIGHT;
	df::Vector start_pos = df::Vector(startX, startY);
	Space s = Space(start_pos, ROOM);
	m->addSpace(s);
	p_hero->setPosition(df::Vector(startX * ROOM_WIDTH + 10, startY * ROOM_HEIGHT + 5));
	WM.setViewFollowing(p_hero);


	int stepsFromStart = 0;
	df::Vector curr_pos = start_pos;
	while (stepsFromStart < (MAP_HEIGHT * MAP_WIDTH - 4)) {
		df::Vector next_pos = generateMove(m, curr_pos);
		if (curr_pos != next_pos) {
			stepsFromStart++;
			curr_pos = next_pos;
		}
	}
	
	// Place stairs
	bool placed = false;
	while (!placed) {
		placed = placeStairs(m, start_pos);
	}

	// Add one Monster
	//TODO generate a random number of monsters?
	Monster* p_monster = new Monster(p_hero);
	//placeObject(new Monster(p_hero));
	p_monster->setPosition(df::Vector(startX * ROOM_WIDTH + 50, startY * ROOM_HEIGHT + 10));


	m->create();
}

bool placeStairs(Map* m, df::Vector start_pos) {
	// Place stairs
	std::vector<Space> spaces = m->getSpaces();
	std::vector<Space>::iterator it = spaces.begin();
	for (it = spaces.begin(); it < spaces.end(); it++) {
		if (it->getPieceType() == ROOM) {
			if (it->getMapPos() != start_pos) {
				int num = rand() % 2;
				if (num == 0) {
					df::Vector room_pos = it->getMapPos();
					// Place stairs
					Stairs* stairs = new Stairs(df::Vector(room_pos.getX() * ROOM_WIDTH + 10, room_pos.getY() * ROOM_HEIGHT + 5));
					LM.writeLog("Placed stairs in room (%d, %d)", room_pos.getX(), room_pos.getY());
					return true;
				}
			}
		}
	}
	return false;

}
// Returns current Position
df::Vector generateMove(Map* m, df::Vector curr_pos) {
	// Pick a random move
	PieceType target_type = ROOM;

	int curr_x = curr_pos.getX();
	int curr_y = curr_pos.getY();

	int num = rand() % 4;
	df::Vector target_space;
	switch (num) {
	case 0:
		target_space = df::Vector(curr_x + 1, curr_y);
		break;
	case 1:
		target_space = df::Vector(curr_x - 1, curr_y);
		break;
	case 2:
		target_space = df::Vector(curr_x, curr_y+1);
		break;
	case 3:
		target_space = df::Vector(curr_x, curr_y-1);
		break;
	}

	// If outside the map, generate again
	int targetX = target_space.getX();
	int targetY = target_space.getY();
	if (targetX >= MAP_WIDTH - 1 || targetX <0 || targetY >= MAP_HEIGHT || targetY < 0) {
		return curr_pos;
	}
	
	// If it has a room around it, generate a hallway
	if (m->getSpaceAt(df::Vector(targetX + 1, targetY)).getPieceType() == ROOM ||
		m->getSpaceAt(df::Vector(targetX - 1, targetY)).getPieceType() == ROOM ||
		m->getSpaceAt(df::Vector(targetX, targetY + 1)).getPieceType() == ROOM ||
		m->getSpaceAt(df::Vector(targetX, targetY - 1)).getPieceType() == ROOM) {
		target_type = HALLWAY;
	}

	// If it is empty, populate it
	if (m->getSpaceAt(target_space).getPieceType() == UNDEFINED_TYPE) {
		Space s = Space(target_space, target_type);
		m->addSpace(s);
	}
	// connect
	m->connectSpacesAt(curr_pos, target_space);

	return target_space;
	

}

// Randomly place Object, making sure no collision. --- taken from professor 
void placeObject(df::Object* p_o) {

	// World dimensions (X,Y).
	int X = (int)WM.getBoundary().getHorizontal();
	int Y = (int)WM.getBoundary().getVertical();

	// Repeat until random (x,y) doesn't have collision for Object.
#ifdef USE_STL
	std::vector<Object*> collision_list;
	df::Vector pos;
	do {
		float x = (float)(rand() % (X - 8) + 4);
		float y = (float)(rand() % (Y - 4) + 2 + 1);
		pos.setXY(x, y);
		collision_list = WM.getCollisions(this, temp_pos);
	} while (!collision_list.empty);
#else
	df::ObjectList collision_list;
	df::Vector pos;
	do {
		float x = (float)(rand() % (X - 8) + 4);
		float y = (float)(rand() % (Y - 4) + 2 + 1);
		pos.setXY(x, y);
		collision_list = WM.getCollisions(p_o, pos);
	} while (!collision_list.isEmpty());
#endif

	// Set position.
	p_o->setPosition(pos);
}


