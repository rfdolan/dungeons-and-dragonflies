#pragma once
// Game includes.
#include "Space.h"
#include "Hero.h"
#include "Vector.h"
#include "Stairs.h"
#include "Monster.h"
#include "Food.h"

#include "Object.h"
#include "Event.h"
#include "EventDeleteInstance.h"

// System includes
#include <vector>

#ifndef MAP_H
#define MAP_H
class Map : public df::Object
{
private:
	std::vector<Space> spaces;
	//Stairs *m_stairs;
	Hero* m_hero;
	//std::vector<Monster*> m_monsters;
	//std::vector<Food*> m_food;
	
	df::Vector generateMove(df::Vector curr_pos);
	bool placeStairs(df::Vector start_pos);
	bool placeMonsters();
	bool placeFood();
	void initialize();
	//void deleteMonsters();
	//void addMonster(Monster* p_monster);
	//void addFood(Food* p_food);
	//void deleteFood();
	//void deleteObject(EventDeleteInstance* p_delete);

public:
	Map();

	void setHero(Hero* p_hero);
	Hero* getHero() const;

	//void setStairs(Stairs* p_stairs);
	//Stairs* getStairs() const;

	// Add a space to the space array, replacing a space if one already exists at the given location
	void addSpace(Space s);

	// Return a vector containing all of the spaces.
	std::vector<Space> getSpaces() const;

	// Return the space at the given location.
	Space getSpaceAt(df::Vector pos) const;

	// Create the level geometry in the world.
	void create();

	// Connect the spaces at the two given positions.
	int connectSpacesAt(df::Vector pos1, df::Vector pos2);

	// Generate a new map randomly.
	void generateMap(Hero* p_hero);

	// Handle stairs event.
	int eventHandler(const df::Event* p_e);
	
	std::vector<Monster*> getMonsters();
};

#endif;
