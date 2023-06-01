#pragma once

#include<iostream>
#include<fstream>

#include"LinkedList.h"
#include"Cargo.h"
#include"Truck.h"
#include"Queue.h"
#include"PriorityQueue.h"
#include"Event.h"
#include"PreparationEvent.h"
#include"CancelEvent.h"
#include"PromptEvent.h"
#include"UI.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

class Company
{
private:
	
	UI* Output;						//pointer to UI
	Time TimeStep;
	
	//Trucks
	
	Queue<Truck*> Normal_Truck_Empty;
	Queue<Truck*> VIP_Truck_Empty;
	Queue<Truck*> Special_Truck_Empty;

	Queue<Truck*> Normal_CheckUp;
	Queue<Truck*> Special_CheckUp;
	Queue<Truck*> VIP_CheckUp;

	PriorityQueue<Truck*> Moving_Trucks;
	PriorityQueue<Truck*> TrucksInReturn;

	//Cargos

	LinkedList<Cargo*> waiting_Normal;
	Queue<Cargo*> waiting_Special;
	PriorityQueue<Cargo*> waiting_VIP;

	Queue<Cargo*> LoadedCargos;

	Queue<Cargo*> Delivered_Cargo;

	//Events

	Queue<Event*> Event_List;

	//Other Data members

	int autoPrompt;
	int DispType;
	int MaxW;
	int maxCDT;
	Time Duration_CU;
	ofstream Output_file;

public:

	Company();
	~Company();

	/////////////////////////////////////////////

	void START();

	/////////////////////////////////////////////

	// Simulation Fucntions:

	void Simulate();

	void ReadInputFile(char* filename);

	void loadVIP ();

	void loadSpecial ();

	void loadNormal ();

	void loadCargoToTruck (Cargo* pCargo , Truck* pTruck);

	void Currently_Delivering();

	void Maintenance();

	void ReturnTrip();

	bool ISEMPTYALL();

	///////////////////////////////////////////// Equations ////////////////////////////////////////

	int PriorityEquation(Cargo* carg);

	int CDT_Calculator(Cargo* carg, Truck* Tr);

	Time WT_Calculator(Cargo* carg);

	///////////////////////////////////////////// UI functions ////////////////////////////////////////

	void PrintCurrentTimeStep();

	void PrintWaitingCargos();

	void PrintEmptyTrucks();

	void PrintMovingCargos();

	void PrintInCheckupTrucks();

	void PrintDeliveredCargos();

	/////////////////////////////////////////// Events Functions //////////////////////////////////////

	void Prepare(Cargo* newCArgo);
	void Cancel( int id);
	void Prompt( int id, int extraMoney);

	/////////////////////////////////////////// Events Functions //////////////////////////////////////

};