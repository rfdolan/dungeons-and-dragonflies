#pragma once
#include "Event.h"
#include "Object.h"

const std::string DELETE_EVENT = "delete_event";
class EventDeleteInstance : public df::Event 
{
private:
	df::Object * m_object;
public:
	EventDeleteInstance(df::Object* p_o);
	df::Object *getObject() const;
};

