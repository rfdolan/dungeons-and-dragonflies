#pragma once
#include "Vector.h"

class Relationship
{
private:
	df::Vector m_pos;
	bool connected;

public:
	Relationship();
	Relationship(df::Vector new_pos);

	void setPos(df::Vector new_pos);
	df::Vector getPos() const;

	void setConnected(bool new_connected);
	bool isConnected() const;
};

