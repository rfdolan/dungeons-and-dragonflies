#pragma once
// Game includes.
#include "Space.h"

// System includes
#include <vector>

#ifndef MAP_H
#define MAP_H
class Map
{
private:
	std::vector<Space> spaces;

public:
	Map();

	void addSpace(Space s);
	std::vector<Space> getSpaces() const;
	Space getSpaceAt(df::Vector pos) const;
	std::vector<Space> getMap() const;
	void create();
	int connectSpacesAt(df::Vector pos1, df::Vector pos2);
};

#endif;
