#pragma once
#include "Relationship.h"

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

	Space(df::Vector new_pos, PieceType type);

	void setPieceType(PieceType type);
	PieceType getPieceType() const;

	void setRelationships(std::vector<Relationship> r);
	std::vector<Relationship> getRelationships() const;

	int addRelationship(Relationship r);

	int connect(df::Vector pos);

	void setMapPos(df::Vector pos);
	df::Vector getMapPos() const;

	void createInWorld();

private:
	PieceType m_piece_type;
	std::vector<Relationship> m_relationships;
	df::Vector map_pos;
	void createRoomInWorld();
	void createHallwayInWorld();

};

#endif;
