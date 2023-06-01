#include "Event.h"


Event:: Event(Time eventTime, int id)
{
	EventTime = eventTime;           
	ID = id;
}

Event::Event()
{
}

void Event::setEventTime(Time x)
{
	EventTime = x;
}

void Event::setID(int x)
{
	ID = x;
}

Time Event:: getEventTime()
{
	return EventTime;
}

int Event:: getID()
{
	return ID;
}

Event::~Event()
{
}
