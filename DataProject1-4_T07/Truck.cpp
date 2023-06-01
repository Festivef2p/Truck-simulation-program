#include"Truck.h"

//Constructors ------------------------------------

Truck::Truck()
{
	setTruck_id(0);
	setTC(0);
	setMaxJ(0);
	setTCSpeed(0);
	setDI(0);
	setMaxD(0);
	setTCD(0);
	setTJ(0);
	setJcount(0);
	setHrsinCheckup(0);
}

Truck::Truck(int truckcapacity,int j,int speed)
{
	setTC(truckcapacity);
	setMaxJ(j);
	setTCSpeed(speed);
	setDI(0);
	setMaxD(0);
	setTCD(0);
	setTJ(0);
	setJcount(0);
	setHrsinCheckup(0);
}

//setters ------------------------------------------

void Truck::setTruck_id(int x)
{
	Truck_id = x;
}

void Truck::setTC(int x)
{
	TC = x;
}

void Truck::setMaxJ(int x)
{
	MaxJ = x;
}

void Truck::setTCSpeed(int x)
{
	Speed = x;
}

void Truck::setDI(int x)
{
	DI = x;
}

void Truck::setMaxD(int x)
{
	MaxD = x;
}

void Truck::setTCD(int x)
{
	TCD = x;
}

void Truck::setTJ(int x)
{
	TJ = x;
}

void Truck::setTTAT(Time x)
{
	TTAT = x;
}

void Truck::setTruck_type(char x)
{
	Truck_type = x;
}

void Truck::setJcount(int x)
{
	Jcount = x;
}

void Truck::setHrsinCheckup(int x)
{
	HrsinCheckup = x;
}

void Truck::setTimeToReturn(int x)
{
	TimeToReturn = x;
}

//getters -----------------------------------------

int Truck::getTC()
{
	return TC;
}

int Truck::getMaxJ()
{
	return MaxJ;
}

int Truck::getSpeed()
{
	return Speed;
}

int Truck::getDI()
{
	return DI;
}

int Truck::getMaxD()
{
	return MaxD;
}

int Truck::getTCD()
{
	return TCD;
}

int Truck::getTJ()
{
	return TJ;
}

Time Truck::getTTAT()
{
	return TTAT;
}

int Truck::getTruck_id()
{
	return Truck_id;
}

char Truck::getTruck_type()
{
	return Truck_type;
}

int Truck::getJcount()
{
	return Jcount;
}

int Truck::getHrsinCheckup()
{
	return HrsinCheckup;
}

int Truck::getTimeToReturn()
{
	return TimeToReturn;
}