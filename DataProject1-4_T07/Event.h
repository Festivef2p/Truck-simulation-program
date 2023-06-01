#pragma once
#include"Time.h"
#include <iostream>
using namespace std;

class Company;	            //Forward declation to pass company pointer

class Event
{
protected:
	Time EventTime;          //Event time and cargo ID are common members for all Event derived classes
	int ID;
public:
	Event(Time eventTime, int id);
	Event();
	
	void setEventTime(Time x);
	void setID(int x);
	Time getEventTime();
	int getID();

	virtual void Execute(Company* pcomp)=0;
	
	virtual ~Event();
};

