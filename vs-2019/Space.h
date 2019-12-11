#pragma once
#include "Relationship.h"
#include "Wall.h"

#include <vector>

#include "Vector.h"
#ifndef SPACE_H
#define SPACE_H
enum PieceType {
	UNDEFINED_TYPE = -1,
	ROOM,
	HALLWAY,
};

class Space
{
public:
	Space();
	~Space();

	Space(df::Vector new_pos, PieceType type);

	void setPieceType(PieceType type);
	PieceType getPieceType() const;

	void setRelationships(std::vector<Relationship> r);
	std::vector<Relationship> getRelationships() const;

	// Add the given relationship to the relationships vector
	int addRelationship(Relationship r);

	// Connect this space to the one at the given position
	int connect(df::Vector pos);

	void setMapPos(df::Vector pos);
	df::Vector getMapPos() const;

	// Create the geometry of the space in the world
	void createInWorld();

	std::vector<Wall*> getWalls();
	// Delete all associated walls
	void deleteWalls();

	void addWall(Wall* p_wall);

private:
	PieceType m_piece_type;
	std::vector<Relationship> m_relationships;
	df::Vector map_pos;
	std::vector<Wall*> m_walls;
	void createRoomInWorld();
	void createHallwayInWorld();

};

#endif;
