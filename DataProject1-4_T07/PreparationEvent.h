#pragma once
#include "Event.h"
#include"Cargo.h"

class PreparationEvent : public Event 
{
	char Type;      
	int Dist;            
	Time LoadingTime;
	int Cost;
public:

	//Constructors

	PreparationEvent();
	PreparationEvent(Time eventTime, int id, char type, int dist, Time loadingTime, int cost);
	
	void Execute(Company* pcomp);

	//setters

	void setType(char x);
	void setDist(int x);
	void setLoadingTime(Time x);
	void setCost(int x);

	//getters

	char getType();
	int getDist();
	Time getLoadingTime();
	int getCost();

	~PreparationEvent();


};

