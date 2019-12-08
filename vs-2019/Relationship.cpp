#include "Relationship.h"

Relationship::Relationship()
{
	connected = false;
}

Relationship::Relationship(df::Vector new_pos)
{
	m_pos = new_pos;
	connected = false;
}

void Relationship::setPos(df::Vector new_pos)
{
	m_pos = new_pos;
}

df::Vector Relationship::getPos() const
{
	return m_pos;
}

void Relationship::setConnected(bool new_connected)
{
	connected = new_connected;
}

bool Relationship::isConnected() const
{
	return connected;
}
