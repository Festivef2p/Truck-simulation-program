#pragma once
#include "Event.h"

class PromptEvent : public Event 
{
	int ExtraMoney;
public:
	PromptEvent(Time eventTime, int id ,int extraMoney);
	~PromptEvent();
	void Execute(Company* pcomp);
};

