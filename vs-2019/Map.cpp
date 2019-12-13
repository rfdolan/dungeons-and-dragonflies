#include "Map.h"
#include "LogManager.h"
#include "game.h"
#include "WorldManager.h"
#include "Monster.h"
#include "Stairs.h"
#include "EventStairs.h"
#include "GameManager.h"
#include "EventGameOver.h"
#include "Food.h"
#include "EventDeleteInstance.h"

Map::Map()
{
	setType("map");
	spaces = std::vector<Space>();
	m_stairs = nullptr;

	registerInterest(STAIRS_EVENT);
	registerInterest(DELETE_EVENT);
	registerInterest(GAME_OVER_EVENT);
}

void Map::setHero(Hero* p_hero)
{
	m_hero = p_hero;
}

Hero* Map::getHero() const
{
	return m_hero;
}

void Map::setStairs(Stairs* p_stairs)
{
	m_stairs = p_stairs;
}

Stairs* Map::getStairs() const
{
	return m_stairs;
}

void Map::addSpace(Space s)
{
	std::vector<Space>::iterator it; 
	std::vector<Space> map = getSpaces();
	for (it = map.begin(); it < map.end(); ) {
		if (it->getMapPos() == s.getMapPos()) {
			it = map.erase(it);
		}
		else {
			it++;
		}
	}
	map.push_back(s);
	spaces = map;
	
}

std::vector<Space> Map::getSpaces() const
{
	return spaces;
}

Space Map::getSpaceAt(df::Vector pos) const
{
	for (Space s : spaces) {
		if (s.getMapPos() == pos) {
			return s;
		}
	}
	// Return an undefined space if the given space does not exist.
	return Space(df::Vector(-1,-1), UNDEFINED_TYPE);
}


void Map::create()
{
	std::vector<Space>::iterator it; 
	for (it = spaces.begin(); it < spaces.end(); it++) {
		//LM.writeLog("Creating a space");
		it->createInWorld();
	}
}

int Map::connectSpacesAt(df::Vector pos1, df::Vector pos2)
{
	int x_diff = abs(pos1.getX() - pos2.getX());
	int y_diff = abs(pos1.getY() - pos2.getY());
	if (x_diff + y_diff != 1) {
		LM.writeLog("Error connecting spaces: spaces must be adjacent");
		return -1;
	}
	Space s1 = getSpaceAt(pos1);
	Space s2 = getSpaceAt(pos2);
	s1.connect(pos2);
	s2.connect(pos1);
	addSpace(s1);
	addSpace(s2);
	return 1;

}

void Map::generateMap(Hero *p_hero) {
	//createTestDungeon();
	LM.writeLog("===GENERATING MAP===");
//	Map* m = new Map();
	m_hero = p_hero;
	// Reset the map.
	initialize();
	LM.writeLog("INITIALIZED");

	// Create start.
	int startX = rand() % MAP_WIDTH;
	int startY = rand() % MAP_HEIGHT;
	df::Vector start_pos = df::Vector(startX, startY);
	Space s = Space(start_pos, ROOM);
	addSpace(s);
	p_hero->setPosition(df::Vector(startX * ROOM_WIDTH + 10, startY * ROOM_HEIGHT + 5));
	WM.setViewFollowing(p_hero);


	int stepsFromStart = 0;
	df::Vector curr_pos = start_pos;
	while (stepsFromStart < (MAP_HEIGHT * MAP_WIDTH - 4)) {
		df::Vector next_pos = generateMove(curr_pos);
		if (curr_pos != next_pos) {
			stepsFromStart++;
			curr_pos = next_pos;
		}
	}
	
	// Place stairs
	bool placed = false;
	while (!placed) {
		placed = placeStairs(start_pos);
	}

	placeMonsters();

	placeFood();

	create();
	LM.writeLog("DONE CREATING LEVEL GEOMETRY");
}

bool Map::placeMonsters() {

	// Place enemy
	//int numPlaced = 0;
	//int numToPlace = (MAP_HEIGHT * MAP_WIDTH / 10) + (rand() % (MAP_HEIGHT * MAP_WIDTH / 2));

	std::vector<Space> spaces = getSpaces();
	std::vector<Space>::iterator it = spaces.begin();
	for (it = spaces.begin(); it < spaces.end(); it++) {
		if (it->getPieceType() == ROOM) {
			int numToPlace = rand() % 4;
			df::Vector room_pos = it->getMapPos();
			switch (numToPlace) {
			case 3:
			{
				Monster* p_monster3 = new Monster(m_hero);
				p_monster3->setPosition(df::Vector(room_pos.getX() * ROOM_WIDTH + 60 + (rand() % 10), room_pos.getY() * ROOM_HEIGHT + 9 + (rand() % 2)));
				addMonster(p_monster3);
			}
			case 2:
			{
				Monster* p_monster2 = new Monster(m_hero);
				p_monster2->setPosition(df::Vector(room_pos.getX() * ROOM_WIDTH + 60 + (rand() % 10), room_pos.getY() * ROOM_HEIGHT + 17 + (rand() % 2)));
				addMonster(p_monster2);
			}
			case 1:
			{
				Monster* p_monster = new Monster(m_hero);
				p_monster->setPosition(df::Vector(room_pos.getX() * ROOM_WIDTH + 15 + (rand() % 4), room_pos.getY() * ROOM_HEIGHT + 17 + (rand() % 2)));
				addMonster(p_monster);
			}
			case 0:
				break;
			}
		}
	}
	return true;
}

bool Map::placeFood()
{
	std::vector<Space> spaces = getSpaces();
	std::vector<Space>::iterator it = spaces.begin();
	for (it = spaces.begin(); it < spaces.end(); it++) {
		if (it->getPieceType() == ROOM) {
			int numToPlace = rand() % 4;
			df::Vector room_pos = it->getMapPos();
			switch (numToPlace) {
			case 3:
			{
				Food* p_food = new Food(rand() % 3);
				p_food->setPosition(df::Vector(room_pos.getX() * ROOM_WIDTH + 15 + (rand() % 4), room_pos.getY() * ROOM_HEIGHT + 17 + (rand() % 2)));
				addFood(p_food);
			}
			case 2:
			{
				Food* p_food2 = new Food(rand() % 3);
				p_food2->setPosition(df::Vector(room_pos.getX() * ROOM_WIDTH + 60 + (rand() % 10), room_pos.getY() * ROOM_HEIGHT + 17 + (rand() % 2)));
				addFood(p_food2);
			}
			case 1:
			{
				Food* p_food3 = new Food(rand() % 3);
				p_food3->setPosition(df::Vector(room_pos.getX() * ROOM_WIDTH + 60 + (rand() % 10), room_pos.getY() * ROOM_HEIGHT + 9 + (rand() % 2)));
				addFood(p_food3);
			}
			case 0:
				break;
			}
		}
	}
	return true;
}

bool Map::placeStairs(df::Vector start_pos) {
	

	/*
	//small food 
	Food* food = new Food(0, df::Vector(start_pos.getX() * ROOM_WIDTH + 10, start_pos.getY() * ROOM_HEIGHT + 10));
	m_food = food;
	LM.writeLog("Placed food in room (%d, %d)", start_pos.getX(), start_pos.getY());
	
	
	//big food
	Food* bigFood= new Food(1, df::Vector(start_pos.getX() * ROOM_WIDTH + 25, start_pos.getY() * ROOM_HEIGHT + 15));
	m_big_food = bigFood;
	LM.writeLog("Placed  big food in room (%d, %d)", start_pos.getX(), start_pos.getY());
	*/
	/*
	Stairs* stairs = new Stairs( df::Vector(start_pos.getX() * ROOM_WIDTH + 25, start_pos.getY() * ROOM_HEIGHT + 15));
	m_stairs = stairs;
	return true;
	*/
	
	// Place stairs
	std::vector<Space> spaces =getSpaces();
	std::vector<Space>::iterator it = spaces.begin();
	for (it = spaces.begin(); it < spaces.end(); it++) {
		if (it->getPieceType() == ROOM) {
			if (it->getMapPos() != start_pos) {
				int num = rand() % 2;
				if (num == 0) {
					df::Vector room_pos = it->getMapPos();
					// Place stairs
					Stairs* stairs = new Stairs(df::Vector(room_pos.getX() * ROOM_WIDTH + 10, room_pos.getY() * ROOM_HEIGHT + 5));
					m_stairs = stairs;
					LM.writeLog("Placed stairs in room (%d, %d)", room_pos.getX(), room_pos.getY());
					return true;
				}
			}
		}
	}
	return false;

}

void Map::initialize()
{
	// Delete all walls
	int numItems = spaces.size();
	for (int i = 0; i < numItems; i++) {
		spaces.pop_back();
	}

	// Delete stairs
	WM.markForDelete(m_stairs);
	// Delete monsters
	deleteMonsters();
	// Delete food
	deleteFood();
	
}

// Returns current Position
df::Vector Map::generateMove(df::Vector curr_pos) {
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
	if (getSpaceAt(df::Vector(targetX + 1, targetY)).getPieceType() == ROOM ||
		getSpaceAt(df::Vector(targetX - 1, targetY)).getPieceType() == ROOM ||
		getSpaceAt(df::Vector(targetX, targetY + 1)).getPieceType() == ROOM ||
		getSpaceAt(df::Vector(targetX, targetY - 1)).getPieceType() == ROOM) {
		target_type = HALLWAY;
	}
	if (rand() % 3 == 0) {
		target_type = HALLWAY;
	}

	// If it is empty, populate it
	if (getSpaceAt(target_space).getPieceType() == UNDEFINED_TYPE) {
		Space s = Space(target_space, target_type);
		addSpace(s);
	}
	// connect
	connectSpacesAt(curr_pos, target_space);

	return target_space;
	

}

int Map::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == STAIRS_EVENT) {
		generateMap(m_hero);
		return 1;
	}
	if (p_e->getType() == DELETE_EVENT) {

		deleteObject((EventDeleteInstance*)p_e);
		return 1;

	}
	if (p_e->getType() == GAME_OVER_EVENT) {
		initialize();
	}
	return 0;
}
std::vector<Monster*> Map::getMonsters()
{
	return m_monsters;
}
void Map::deleteMonsters()
{
	LM.writeLog("DELETING MONSTERS");
	for (int i = 0; i < m_monsters.size(); i++) {
		LM.writeLog("Deleting a monster");
		WM.markForDelete(m_monsters[i]);
	}
	m_monsters.clear();
}
void Map::addMonster(Monster* p_monster)
{
	m_monsters.push_back(p_monster);
}

void Map::addFood(Food* p_food)
{
	m_food.push_back(p_food);
}

void Map::deleteFood()
{
	for (int i = 0; i < m_food.size(); i++) {
		WM.markForDelete(m_food[i]);
		LM.writeLog("Deleting a food");
	}
	m_food.clear();
}

void Map::deleteObject(EventDeleteInstance* p_delete)
{
	if (p_delete->getObject()->getType() == "Food") {
		Food* f = (Food*)p_delete->getObject();
		std::vector<Food*> newVector = std::vector<Food*>();
		for (int i = 0; i < m_food.size(); i++) {
			if (!(m_food[i]->getId() == f->getId())) {
				newVector.push_back(m_food[i]);
			}
			else {
				WM.markForDelete(f);
				LM.writeLog("Deleting a fruit from the list");
			}

		}
		m_food = newVector;

	}
	if (p_delete->getObject()->getType() == "Monster") {
		Monster* f = (Monster*)p_delete->getObject();
		std::vector<Monster*> newVector = std::vector<Monster*>();
		for (int i = 0; i < m_monsters.size(); i++) {
			if (!(m_monsters[i]->getId() == f->getId())) {
				newVector.push_back(m_monsters[i]);
			}
			else {
				WM.markForDelete(f);
				LM.writeLog("Deleting a monster from the list");
			}

		}
		m_monsters = newVector;

	}

}
