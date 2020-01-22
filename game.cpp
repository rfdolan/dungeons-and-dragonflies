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
#include "vs-2019\Food.h"
#include "vs-2019\FloorNum.h"
#include "vs-2019\GameStart.h"

//functions
void loadResources();
void populateWorld();
void createTestDungeon();
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
	RM.loadSprite("../sprites/hero-walk-spr.txt", "walk");
	RM.loadSprite("../sprites/stairs-spr.txt", "stairs");
	RM.loadSprite("../sprites/hero_hurt-spr.txt", "hurt");
	RM.loadSprite("../sprites/hero-attack-spr.txt", "attack");
	RM.loadSprite("../sprites/hero-dead-spr.txt", "dead");
	RM.loadSprite("../sprites/hero-dead-2-spr.txt", "dead2");

	//monster sprites
	RM.loadSprite("../sprites/monster-walk-spr.txt", "monster-walk");
	RM.loadSprite("../sprites/monster-chase-spr.txt", "monster-chase");
	RM.loadSprite("../sprites/monster-hurt01-spr.txt", "monster-hurt1");
	RM.loadSprite("../sprites/monster-hurt02-spr.txt", "monster-hurt2");
	RM.loadSprite("../sprites/monster-hurt03-spr.txt", "monster-hurt3");

	//food
	RM.loadSprite("../sprites/food-spr.txt", "food");
	RM.loadSprite("../sprites/big-food-spr.txt", "big-food");

	//other
	RM.loadMusic("../music/ambient-1.wav", "ambient-1");
	RM.loadSound("../music/attack.wav", "attack");
	RM.loadSound("../music/small_food.wav", "small_food");
	RM.loadSound("../music/big_food.wav", "big_food");
	RM.loadSprite("../sprites/attack-obj-spr.txt", "attack_obj");
	RM.loadSprite("../sprites/game-start-spr.txt", "gamestart");


}

void populateWorld() {

	WM.setBoundary(df::Box(df::Vector(0, 0), (ROOM_WIDTH * MAP_WIDTH) + 1, (ROOM_HEIGHT * MAP_HEIGHT) + 1));
	float X = WM.getBoundary().getHorizontal();
	float Y = WM.getBoundary().getVertical();


	new GameStart();

	/*
	//populate hunger
	new Hunger;
	new FloorNum;

	Map* m = new Map();
	// Generate world.
	m->generateMap(p_hero);

	RM.getMusic("ambient-1")->play();
	*/
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


