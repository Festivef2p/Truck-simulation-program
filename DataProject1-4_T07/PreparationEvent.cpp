#include "PreparationEvent.h"
#include "Company.h"

//Constructors

PreparationEvent::PreparationEvent()
{
}

PreparationEvent::PreparationEvent(Time eventTime, int id, char type, int dist, Time loadingTime, int cost) :Event (eventTime,id)
{
	Type = type;
	Dist = dist;
	LoadingTime = loadingTime;
	Cost = cost;
}

//Specific Functions

void PreparationEvent:: Execute(Company* pcomp)
{
	Cargo* newCargo = new Cargo(Type , ID , EventTime , LoadingTime , Dist , Cost);
	pcomp->Prepare(newCargo);
}

//setters

void PreparationEvent::setType(char x)
{
	Type = x;
}

void PreparationEvent::setDist(int x)
{
	Dist = x;
}

void PreparationEvent::setLoadingTime(Time x)
{
	LoadingTime = x;
}

void PreparationEvent::setCost(int x)
{
	Cost = x;
}

//getters

char PreparationEvent::getType()
{
	return Type;
}

int PreparationEvent::getDist()
{
	return Dist;
}

Time PreparationEvent::getLoadingTime()
{
	return LoadingTime;
}

int PreparationEvent::getCost()
{
	return Cost;
}

//Destructors

PreparationEvent::~PreparationEvent()
{
}