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
#include "vs-2019\Monster.h"
#include "vs-2019\Hunger.h"

//functions
void loadResources();
void populateWorld();
void placeObject(df::Object* p_o);


int main(void) {
	srand((unsigned int)time(NULL));

  // Start up game manager.
  if (GM.startUp())  {
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

	float X = WM.getBoundary().getHorizontal();
	float Y = WM.getBoundary().getVertical();

	// Generate world.
	// TODO add basic walls for testing
	Hero* p_hero = new Hero;
	df::Vector hero_pos = df::Vector(10, 5);
	p_hero->setPosition(hero_pos);
	LM.writeLog("Placed hero");

	// Add one Monster
	//TODO generate a random number of monsters?
	//Monster* p_monster = new Monster(p_hero);
	placeObject(new Monster(p_hero));

	//populate hunger
	new Hunger;
	

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


