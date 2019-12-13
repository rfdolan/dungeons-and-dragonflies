#include "EventDeleteInstance.h"

EventDeleteInstance::EventDeleteInstance(df::Object* p_o)
{
	m_object = p_o;
	setType(DELETE_EVENT);
}

df::Object* EventDeleteInstance::getObject() const
{
	return m_object;
}
