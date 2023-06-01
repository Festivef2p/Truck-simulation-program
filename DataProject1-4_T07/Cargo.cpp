#include"Cargo.h"


//Constructors

	Cargo::Cargo()
	{
	
	}

	Cargo::Cargo(char ct,int i,Time pt,Time lt,int dd,int c)
	{
		setCargoType(ct);
		setid(i);
		setPrepTime(pt);
		setLoadTime(lt);
		setDeliveryDis(dd);
		setCost(c);
	}

	//setters

	void Cargo::setCargoType(char x)
	{
		CargoType = x;
	}

	void Cargo::setid(int x)
	{
		id = x;
	}

	void Cargo::setPrepTime(Time x)
	{
		PrepTime = x;
	}

	void Cargo::setLoadTime(Time x)
	{
		LoadTime = x;
	}

	void Cargo::setCDT(Time x)
	{
		CDT = x;
	}

	void Cargo::setWT(Time x)
	{
		WT = x;
	}

	void Cargo::setDeliveryDis(int x)
	{
		DeliveryDis = x;
	}

	void Cargo::setCost(int x)
	{
		Cost = x;
	}

	void Cargo::setCDT(int x)
	{
		CDT.hour = x;
	}

	//getters

	char Cargo::getCargoType()
	{
		return CargoType;
	}

	int Cargo::getid()
	{
		return id;
	}

	Time Cargo::getPrepTime()
	{
		return PrepTime;
	}

	Time Cargo::getLoadTime()
	{
		return LoadTime;
	}

	Time Cargo::getCDT()
	{
		return CDT;
	}

	Time Cargo::getWT()
	{
		return WT;
	}

	int Cargo::getDeliveryDis()
	{
		return DeliveryDis;
	}

	int Cargo::getCost()
	{
		return Cost;
	}