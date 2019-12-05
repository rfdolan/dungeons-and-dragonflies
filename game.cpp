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

void loadResources();
void populateWorld();

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
	RM.loadSprite("sprites/hero-walk-spr.txt", "walk");
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
}

