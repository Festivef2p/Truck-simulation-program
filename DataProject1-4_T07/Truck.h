#pragma once
#include"Cargo.h"
#include"PriorityQueue.h"

class Truck
{
private:

	int Truck_id;					 // id of each truck
	int TC;							 // Truck Capacity
	int MaxJ;					     // Number of Journeys before checkup
	int Jcount;						 // Number of finished jourenys
	int MaxD;						 // Max distance of cargo in storage
	int TCD;						 // Total cargos delivered
	int TJ;							 // Total journeys made
	Time TTAT;						 // Total truck active time
	int Speed;						 // Speed of the trucks
	int DI;							 // Delivery interval
	char Truck_type;				 // Type : N , VIP , S
	int HrsinCheckup;
	int TimeToReturn;
	

public:

	//Constructors

	Truck();
	Truck(int truckcapacity,int checkup,int speed);

	//setters

	void setTruck_id(int x);
	void setTC(int x);
	void setMaxJ(int x);
	void setTCSpeed(int x);
	void setDI(int x);
	void setMaxD(int x);
	void setTCD(int x);
	void setTJ(int x);
	void setTTAT(Time x);
	void setTruck_type(char x);
	void setJcount(int x);
	void setHrsinCheckup(int x);
	void setTimeToReturn(int x);

	//getters

	int getTC();
	int getMaxJ();
	int getSpeed();
	int getDI();
	int getMaxD();
	int getTCD();
	int getTJ();
	Time getTTAT();
	int getTruck_id();
	char getTruck_type();
	int getJcount();
	int getHrsinCheckup();
	int getTimeToReturn();

	PriorityQueue<Cargo*> CargoInisdeTruck;
};