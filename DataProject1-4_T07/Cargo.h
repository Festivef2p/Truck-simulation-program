#pragma once
#include"Time.h"

class Cargo
{
private:
	char CargoType;        //Normal,Special or VIP
	int id;					
	Time PrepTime;
	Time LoadTime;
	int DeliveryDis;
	int Cost;
	Time CDT;
	Time WT;
public:

	//Constructors

	Cargo();
	Cargo(char ct,int i,Time pt,Time lt,int dd,int c);

	//setters

	void setCargoType(char x);
	void setid(int x);
	void setPrepTime(Time x);
	void setLoadTime(Time x);
	void setCDT(Time x);
	void setWT(Time x);
	void setDeliveryDis(int x);
	void setCost(int x);
	void setCDT(int x);

	//getters

	char getCargoType();
	int getid();
	Time getPrepTime();
	Time getLoadTime();
	Time getCDT();
	Time getWT(); /////////////////
	int getDeliveryDis();
	int getCost();

};