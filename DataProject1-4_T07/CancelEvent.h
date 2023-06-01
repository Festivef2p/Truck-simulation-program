#pragma once
#include "Event.h"

class CancelEvent : public Event 
{
public:
	CancelEvent(Time eventTime, int id);
	~CancelEvent();
	void Execute(Company* pcomp);
};

