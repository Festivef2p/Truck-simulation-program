#include "PromptEvent.h"
#include "Company.h"

PromptEvent::PromptEvent(Time eventTime, int id, int extraMoney) :Event (eventTime,id)
{
	ExtraMoney = extraMoney;
}

PromptEvent::~PromptEvent()
{
}

void PromptEvent:: Execute(Company* pcomp)
{
	pcomp->Prompt(ID , ExtraMoney);
}