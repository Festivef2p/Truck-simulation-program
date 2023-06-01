#include "CancelEvent.h"
#include "Company.h"

CancelEvent::CancelEvent(Time eventTime, int id) :Event (eventTime,id)
{
}

CancelEvent::~CancelEvent()
{
}

void CancelEvent:: Execute(Company* pcomp)
{
	pcomp->Cancel(ID);
}