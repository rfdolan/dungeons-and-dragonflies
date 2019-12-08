#include "Map.h"
#include "LogManager.h"

Map::Map()
{
	spaces = std::vector<Space>();
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

std::vector<Space> Map::getMap() const
{
	return spaces;
}

void Map::create()
{
	std::vector<Space>::iterator it; 
	std::vector<Space> map = getSpaces();
	for (it = map.begin(); it < map.end(); it++) {
		LM.writeLog("Creating a space");
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
