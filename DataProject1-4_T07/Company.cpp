#include "Company.h"

//Constructors

Company::Company()
{
	TimeStep.Day = 1;
	TimeStep.hour = 1;
	maxCDT = 0;
	Output_file.open("Stats.txt");
}


void Company::START()
{
	char* Filename;
	UI InOut;
	Filename = InOut.ReadFileName();
	ReadInputFile(Filename);
	switch(InOut.ModeSelect())
	{
	case 1:
		DispType = 1;
		Simulate();
	case 2:
		DispType = 2;
		Simulate();
	case 3:
		DispType = 3;
		Simulate();
		cout << "Statistics Generated!" << endl;
	}
}

///////////////////////////////////////////// Simulation Fucntions ////////////////////////////////////////

void Company::Simulate()
{
	Event* CurrentEvent;
	Output_file << "CDT   ID PT   WT   TID" << endl;
	while(ISEMPTYALL())
	{
		Event_List.peekFront(CurrentEvent);
		while(TimeStep.hour >= 5 && TimeStep.hour <=23)
		{
			Event_List.peekFront(CurrentEvent);
			if(CurrentEvent->getEventTime().Day == TimeStep.Day && CurrentEvent->getEventTime().hour == TimeStep.hour)
			{
				CurrentEvent->Execute(this);
			}
			loadVIP();
			loadNormal();
			loadSpecial();
			Currently_Delivering();
			Maintenance();
			ReturnTrip();
			if(CurrentEvent->getEventTime().Day == TimeStep.Day && CurrentEvent->getEventTime().hour == TimeStep.hour)
				Event_List.dequeue(CurrentEvent);
			if(DispType == 1)
				Output->Disp_INT(this);
			else if(DispType == 2)
			{
				Output->Disp_STS(this);
				Sleep(1000);
			}
			TimeStep.hour++;
			TimeStep.TimeIncDay();
		}
		if(CurrentEvent->getEventTime().Day == TimeStep.Day && CurrentEvent->getEventTime().hour == TimeStep.hour)
		{
			Event_List.dequeue(CurrentEvent);
		}
		Currently_Delivering();
		Maintenance();
		ReturnTrip();
		if(DispType == 1)
			Output->Disp_INT(this);
		else if(DispType == 2)
		{
			Output->Disp_STS(this);
			Sleep(1000);
		}
		TimeStep.hour++;
		TimeStep.TimeIncDay();

	}
	Output_file << "........................................" << endl;
	Output_file << "........................................" << endl;
	Output_file << "Cargos: " << Delivered_Cargo.getCounter();
}

///////////////////////////////////////////////////////////////// load functions ////////////////////////////////////////////////////

//-------------------------------------------------------------loadVIP--------------------------------------------
void Company:: loadVIP ()
{	Cargo* pCargo;
	Truck* pTruck;                                              //Truck ptr to store the dequeued Truck
	bool findMW = false;
	//////////////////////////////////////////////////////////////////////////////// MW case
	for(int i=0;i<waiting_VIP.getCount();i++)
	{
		
		waiting_VIP.dequeue(pCargo);
		pCargo->setWT(WT_Calculator(pCargo));

		if ( pCargo->getWT().ChangetoHoursFormat() >= MaxW )                //finding cargo with MWT
		{
			VIP_Truck_Empty.dequeue(pTruck);
			loadCargoToTruck( pCargo , pTruck );
			findMW = true;
			break;
		}
		else 
		{
			waiting_VIP.enqueue(pCargo , PriorityEquation(pCargo) );
		}
	}

	if (findMW)
	{
		Moving_Trucks.enqueue(pTruck,INT_MAX - pCargo->getCDT().ChangetoHoursFormat());
		return;
	}
	///////////////////////////////////////////////////////////////////////////////// no-MW case
	if ( !VIP_Truck_Empty.isEmpty()  )							  
	{
		VIP_Truck_Empty.dequeue(pTruck);						  //getting an empty truck to get its CT
		if ( pTruck->getTC() <= waiting_VIP.getCount() )
		{
			for (int i=0 ; i< pTruck->getTC() ; i++)              //loop to fill the truck with cargos
			{
				Cargo* pcargo;
				waiting_VIP.dequeue(pcargo);
				loadCargoToTruck( pcargo , pTruck );

			}
		}
		else 
		{
			VIP_Truck_Empty.enqueue(pTruck);
		}
	}
	else if (!Normal_Truck_Empty.isEmpty())
	{
		Normal_Truck_Empty.dequeue(pTruck);
		if ( pTruck->getTC() <= waiting_VIP.getCount() )
		{
			for (int i=0 ; i< pTruck->getTC() ; i++)
			{
				Cargo* pcargo;
				waiting_VIP.dequeue(pcargo);
				loadCargoToTruck( pcargo , pTruck );
			}
		}
		else 
		{
			Normal_Truck_Empty.enqueue(pTruck);
		}
	}
	else if (!Special_Truck_Empty.isEmpty())
	{
		Special_Truck_Empty.dequeue(pTruck);
		if ( pTruck->getTC() <= waiting_VIP.getCount() )
		{
			for (int i=0 ; i< pTruck->getTC() ; i++)
			{
				Cargo* pcargo;
				waiting_VIP.dequeue(pcargo);
				loadCargoToTruck( pcargo , pTruck );
			}
		}
		else 
		{
			Special_Truck_Empty.enqueue(pTruck);
		}
	}

}

//-------------------------------------------------------------loadSpecial--------------------------------------------
void Company:: loadSpecial ()
{
	Cargo* pCargo;
	Truck* pTruck;                                              //Truck ptr to store the dequeued Truck
	bool findMW = false;
	//////////////////////////////////////////////////////////////////////////////// MW case
	for(int i=0;i<waiting_Special.getCounter();i++)
	{
		waiting_Special.dequeue(pCargo);
		pCargo->setWT(WT_Calculator(pCargo));

		if ( pCargo->getWT().ChangetoHoursFormat() >= MaxW )                //finding cargo with MWT
		{
			Special_Truck_Empty.dequeue(pTruck);
			loadCargoToTruck( pCargo , pTruck );
			findMW = true;
			break;
		}
		else 
		{
			waiting_Special.enqueue(pCargo);
		}
	}

	if (findMW)
	{
		Moving_Trucks.enqueue(pTruck,INT_MAX - pCargo->getCDT().ChangetoHoursFormat());
		return;
	}
	///////////////////////////////////////////////////////////////////////////////// no-MW case
	if (!Special_Truck_Empty.isEmpty())
	{
		Special_Truck_Empty.dequeue(pTruck);
		if ( pTruck->getTC() <= waiting_Special.getCounter() )
		{
			for (int i=0 ; i< pTruck->getTC() ; i++)
			{
				Cargo* pcargo;
				waiting_Special.dequeue(pcargo);
				loadCargoToTruck( pcargo , pTruck );
			}
		}
		else 
		{
			Special_Truck_Empty.enqueue(pTruck);
		}
	}
}

//-------------------------------------------------------------loadNormal--------------------------------------------
void Company:: loadNormal ()
{	Cargo* pCargo;
	Truck* pTruck;                                              //Truck ptr to store the dequeued Truck
	bool findMW = false;
	//////////////////////////////////////////////////////////////////////////////// MW case
	for(int i=0;i<waiting_Normal.getCounter();i++)
	{
		
		waiting_Normal.DeleteFirst(pCargo);
		pCargo->setWT(WT_Calculator(pCargo));
		if ( pCargo->getWT().ChangetoHoursFormat() >= MaxW )                //finding cargo with MWT
		{
			Normal_Truck_Empty.dequeue(pTruck);
			loadCargoToTruck( pCargo , pTruck );
			findMW = true;
			break;
		}
		else 
		{
			waiting_Normal.InsertEnd(pCargo);
		}
	}

	if (findMW)
	{
		Moving_Trucks.enqueue(pTruck,INT_MAX - pCargo->getCDT().ChangetoHoursFormat());
		return;
	}
	///////////////////////////////////////////////////////////////////////////////// no-MW case
	if (!Normal_Truck_Empty.isEmpty())
	{
		Normal_Truck_Empty.dequeue(pTruck);
		if ( pTruck->getTC() <= waiting_Normal.getCounter() )
		{
			for (int i=0 ; i< pTruck->getTC() ; i++)
			{
				Cargo* pcargo;
				waiting_Normal.DeleteFirst(pcargo);
				loadCargoToTruck( pcargo , pTruck );
			}
		}
		else 
		{
			Normal_Truck_Empty.enqueue(pTruck);
		}
	}
	else if ( !VIP_Truck_Empty.isEmpty()  )
	{
		VIP_Truck_Empty.dequeue(pTruck);
		if ( pTruck->getTC() <= waiting_Normal.getCounter() )
		{
			for (int i=0 ; i< pTruck->getTC() ; i++)
			{
				Cargo* pcargo;
				waiting_Normal.DeleteFirst(pcargo);
				loadCargoToTruck( pcargo , pTruck );
			}
		}
		else 
		{
			VIP_Truck_Empty.enqueue(pTruck);
		}
	}

}

void Company::loadCargoToTruck( Cargo* pCargo , Truck* pTruck )
{
	pTruck->CargoInisdeTruck.enqueue(pCargo , INT_MAX - CDT_Calculator(pCargo,pTruck) );
	LoadedCargos.enqueue(pCargo);
	pCargo->setWT( WT_Calculator(pCargo) );
	pCargo->setCDT( CDT_Calculator(pCargo , pTruck) );
	if(pCargo->getCDT().ChangetoHoursFormat() > maxCDT)
	{
		maxCDT = pCargo->getCDT().ChangetoHoursFormat();
		pTruck->setMaxD(pCargo->getDeliveryDis());
	}
	if(pTruck->CargoInisdeTruck.getCount() == pTruck->getTC())
		Moving_Trucks.enqueue(pTruck,INT_MAX - maxCDT);
}

void Company::Currently_Delivering()
{
	if(!Moving_Trucks.isEmpty())
	{
		Truck* TR;
		Cargo* carg;
		Cargo* trash;
		Moving_Trucks.peekFront(TR);
		TR->CargoInisdeTruck.peekFront(carg);
		if(TimeStep.ChangetoHoursFormat() >= carg->getCDT().ChangetoHoursFormat())
		{
			TR->CargoInisdeTruck.dequeue(carg);
			TR->setTCD(TR->getTCD()+1);
			Delivered_Cargo.enqueue(carg);
			LoadedCargos.dequeue(trash);
			Time CDTDH;
			CDTDH.ChangetoDayHourForamt(carg->getCDT().ChangetoHoursFormat());
			Output_file << CDTDH.Day << ":" << CDTDH.hour << "  " << carg->getid() << "  " << carg->getPrepTime().Day << ":" << carg->getPrepTime().hour << "  ";
			Output_file << carg->getWT().Day << ":" << carg->getWT().hour << "  " << TR->getTruck_id() << endl;

			Moving_Trucks.dequeue(TR);
			if(TR->CargoInisdeTruck.isEmpty())
			{
				TR->setJcount(TR->getJcount() + 1);
				TR->setTJ(TR->getTJ()+1);
				if(TR->getJcount() == TR->getMaxJ())
				{
					TR->setJcount(0);
					if(TR->getTruck_type() == 'N')
						Normal_CheckUp.enqueue(TR);
					if(TR->getTruck_type() == 'V')
						VIP_CheckUp.enqueue(TR);
					else if(TR->getTruck_type() == 'S')
						Special_CheckUp.enqueue(TR);
				}
				else
				{
					TrucksInReturn.enqueue(TR,INT_MAX - (TR->getMaxD()/TR->getSpeed()));
					int time = TimeStep.ChangetoHoursFormat() + (TR->getMaxD()/TR->getSpeed());
					TR->setTimeToReturn(time);
				}
			}
			else
			{
				TR->CargoInisdeTruck.peekFront(carg);
				Moving_Trucks.enqueue(TR,INT_MAX - (CDT_Calculator(carg,TR)));
			}
		}
	}
}

void Company::Maintenance()
{
	Truck* TR;
	for(int i = 0; i<Normal_CheckUp.getCounter(); i++)
	{
		Normal_CheckUp.dequeue(TR);
		TR->setHrsinCheckup(TR->getHrsinCheckup() + 1);
		if(TR->getHrsinCheckup() == Duration_CU.hour)
		{
			TR->setHrsinCheckup(0);
			Normal_Truck_Empty.enqueue(TR);
		}
		else
		{
			Normal_CheckUp.enqueue(TR);
		}
	}
	for(int i = 0; i<VIP_CheckUp.getCounter(); i++)
	{
		VIP_CheckUp.dequeue(TR);
		TR->setHrsinCheckup(TR->getHrsinCheckup() + 1);
		if(TR->getHrsinCheckup() == Duration_CU.hour)
		{
			TR->setHrsinCheckup(0);
			VIP_Truck_Empty.enqueue(TR);
		}
		else
		{
			VIP_CheckUp.enqueue(TR);
		}
	}
	for(int i = 0; i<Special_CheckUp.getCounter(); i++)
	{
		Special_CheckUp.dequeue(TR);
		TR->setHrsinCheckup(TR->getHrsinCheckup() + 1);
		if(TR->getHrsinCheckup() == Duration_CU.hour)
		{
			TR->setHrsinCheckup(0);
			Special_Truck_Empty.enqueue(TR);
		}
		else
		{
			Special_CheckUp.enqueue(TR);
		}
	}
}

void Company::ReturnTrip()
{
	Truck* TR;
	PriorityQueue<Truck*> Temp;
	while(!TrucksInReturn.isEmpty())
	{
		TrucksInReturn.dequeue(TR);
		if(TimeStep.ChangetoHoursFormat() == TR->getTimeToReturn())
		{
			TR->setTimeToReturn(0);
			if(TR->getTruck_type() == 'N')
				Normal_Truck_Empty.enqueue(TR);
			else if(TR->getTruck_type() == 'V')
				VIP_Truck_Empty.enqueue(TR);
			else if(TR->getTruck_type() == 'S')
				Special_Truck_Empty.enqueue(TR);
		}
		else
			Temp.enqueue(TR,INT_MAX -(TR->getMaxD()/TR->getSpeed()));
	}
	while(!Temp.isEmpty())
	{


		Temp.dequeue(TR);
		TrucksInReturn.enqueue(TR,INT_MAX - (TR->getMaxD()/TR->getSpeed()));
	}
}

///////////////////////////////////////////// VIP Cargo Priority Equation ////////////////////////////////////////

int Company::PriorityEquation(Cargo* carg)
{
	return 0.5*(carg->getPrepTime()).getDay() + 0.5*(carg->getPrepTime()).getHour() + 0.7*carg->getDeliveryDis() + 0.9*carg->getCost();
}

///////////////////////////////////////////// CDT Calculator ////////////////////////////////////////

int Company::CDT_Calculator(Cargo* carg,Truck* Tr)
{

	int TimeStep_Allhrs = TimeStep.ChangetoHoursFormat();											//Changes the Days to hours and adds it to its hours
	int LoadTime_Allhrs = carg->getLoadTime().ChangetoHoursFormat();								//Changes the Days to hours and adds it to its hours
	return TimeStep_Allhrs + carg->getDeliveryDis()/Tr->getSpeed() + LoadTime_Allhrs;				//Equation of CDT in hours

}

///////////////////////////////////////////// WT Calculator ////////////////////////////////////////

Time Company::WT_Calculator(Cargo* carg)
{
	Time WT;
	int TimeStep_Allhrs = TimeStep.ChangetoHoursFormat();
	int PrepTime_Allhrs = carg->getPrepTime().ChangetoHoursFormat();
	int Total_hrs = TimeStep_Allhrs - PrepTime_Allhrs;
	WT.ChangetoDayHourForamt(Total_hrs);
	return WT;
}

///////////////////////////////////////////// UI functions ////////////////////////////////////////

void Company::ReadInputFile(char* filename)
{
	ifstream Input_file;
	Input_file.open(filename);

	int N_Trucknumber, VIP_Trucknumber, S_Trucknumber;
	int N_Truckspeed, VIP_Truckspeed, S_Truckspeed;
	int N_Truckcapacity, VIP_Truckcapacity, S_Truckcapacity;
	int N_TruckJCU, VIP_TruckJCU, S_TruckJCU, checkup_duration;	//number of journeys before checkups and duration
	int Eventnum;

	Input_file >> N_Trucknumber >> S_Trucknumber >> VIP_Trucknumber;
	Input_file >> N_Truckspeed >> S_Truckspeed >> VIP_Truckspeed;
	Input_file >> N_Truckcapacity >> S_Truckcapacity >> VIP_Truckcapacity;
	Input_file >> N_TruckJCU >> S_TruckJCU >> VIP_TruckJCU >> checkup_duration;
	Input_file >> autoPrompt >> MaxW;
	Input_file >> Eventnum;

	Duration_CU.hour = checkup_duration;

	for(int i=0; i<N_Trucknumber;i++)
	{
		Truck* newNormalTruck = new Truck(N_Truckcapacity,N_TruckJCU,N_Truckspeed);
		newNormalTruck->setTruck_id(i);
		newNormalTruck->setTruck_type('N');
		Normal_Truck_Empty.enqueue(newNormalTruck);
	}

	for(int i=0; i<VIP_Trucknumber;i++)
	{
		Truck* newVIPTruck = new Truck(VIP_Truckcapacity,VIP_TruckJCU,VIP_Truckspeed);
		newVIPTruck->setTruck_id(i);
		newVIPTruck->setTruck_type('V');
		VIP_Truck_Empty.enqueue(newVIPTruck);
	}

	for(int i=0; i<S_Trucknumber;i++)
	{
		Truck* newSpecialTruck = new Truck(S_Truckcapacity,S_TruckJCU,S_Truckspeed);
		newSpecialTruck->setTruck_id(i);
		newSpecialTruck->setTruck_type('S');
		Special_Truck_Empty.enqueue(newSpecialTruck);
	}


	Event* newEvent;
	char x;
	int Event_counter = 0;
	while(Input_file.good() && Event_counter < Eventnum)
	{
		Input_file >> x;
		if(x == 'R')
		{
			char type;
			int id, dist, cost;
			Time loadtime, preptime;

			Input_file >> type;
			Input_file >> preptime.Day;
			Input_file.ignore();
			Input_file >> preptime.hour;
			Input_file >> id;
			Input_file >> dist;
			Input_file >> loadtime.hour;
			Input_file >> cost;

			PreparationEvent* new_prep_Event = new PreparationEvent(preptime,id,type,dist,loadtime,cost);
			newEvent = new_prep_Event;
			Event_List.enqueue(newEvent);
			Event_counter++;
		}
		else if(x == 'X')
		{
			Time EventTime;
			int id;
			Input_file >> EventTime.Day;
			Input_file.ignore();
			Input_file >> EventTime.hour;
			Input_file >> id;
			CancelEvent* new_cancel_event = new CancelEvent(EventTime,id);
			newEvent = new_cancel_event;
			Event_List.enqueue(newEvent);
			Event_counter++;
		}
		else if(x == 'P')
		{
			Time EventTime;
			int  id, extra_money;
			Input_file >> EventTime.Day;
			Input_file.ignore();
			Input_file >> EventTime.hour;
			Input_file >> id;
			Input_file >> extra_money;
			PromptEvent* new_prompt_event = new PromptEvent(EventTime,id,extra_money);
			newEvent = new_prompt_event;
			Event_List.enqueue(newEvent);
			Event_counter++;
		}
	}
}

bool Company::ISEMPTYALL()
{
	if(!Event_List.isEmpty() || !waiting_Normal.isEmpty() || !waiting_Special.isEmpty()|| !waiting_VIP.isEmpty() || !Moving_Trucks.isEmpty() || !Normal_CheckUp.isEmpty() || !VIP_CheckUp.isEmpty() || !Special_CheckUp.isEmpty() || !LoadedCargos.isEmpty())
		return true;
	else
		return false;
}

/////////////////////////////////// Print Functions //////////////////////////////////////

void Company::PrintMovingCargos()
{
	Cargo* TempCargo;
	Truck* TempTruck;
	PriorityQueue<Truck*> TempTruckQueue;
	PriorityQueue<Cargo*> TempCargoQueue;
	int CountCargos = 0;
	int no1=0;
	while(!Moving_Trucks.isEmpty())
	{
		Moving_Trucks.dequeue(TempTruck);
		CountCargos = CountCargos + TempTruck->CargoInisdeTruck.getCount();
		no1++;
		TempTruckQueue.enqueue(TempTruck,INT_MAX - no1);
	}
	cout << CountCargos << " " << "Moving Cargos ";
	while(!TempTruckQueue.isEmpty())
	{
		int no2 =0;
		TempTruckQueue.dequeue(TempTruck);
		//////////// Printing Normal  /////////
		if(TempTruck->getTruck_type() == 'N')
		{
			cout << TempTruck->getTruck_id();
			cout << "[";
			while(!TempTruck->CargoInisdeTruck.isEmpty())
			{
				TempTruck->CargoInisdeTruck.dequeue(TempCargo);
				cout << TempCargo->getid();
				TempCargoQueue.enqueue(TempCargo,no2);
				no2++;
				if(!TempTruck->CargoInisdeTruck.isEmpty())
					cout << ",";
			}
			cout << "]" << " ";
			no2 = 1;
			while(!TempCargoQueue.isEmpty())
			{
				TempCargoQueue.dequeue(TempCargo);
				TempTruck->CargoInisdeTruck.enqueue(TempCargo,no2);
				no2++;
			}
			TempTruck->CargoInisdeTruck.peekFront(TempCargo);
			Moving_Trucks.enqueue(TempTruck,INT_MAX - (CDT_Calculator(TempCargo,TempTruck)));
		}
		//////////// Printing Special /////////
		else if(TempTruck->getTruck_type() == 'S')
		{
			cout << TempTruck->getTruck_id();
			cout << "(";
			while(!TempTruck->CargoInisdeTruck.isEmpty())
			{
				TempTruck->CargoInisdeTruck.dequeue(TempCargo);
				cout << TempCargo->getid();
				TempCargoQueue.enqueue(TempCargo,no2);
				no2++;
				if(!TempTruck->CargoInisdeTruck.isEmpty())
					cout << ",";
			}
			cout << ")" << " ";
			no2 = 1;
			while(!TempCargoQueue.isEmpty())
			{
				TempCargoQueue.dequeue(TempCargo);
				TempTruck->CargoInisdeTruck.enqueue(TempCargo,no2);
				no2++;
			}
			TempTruck->CargoInisdeTruck.peekFront(TempCargo);
			Moving_Trucks.enqueue(TempTruck,INT_MAX - CDT_Calculator(TempCargo,TempTruck));
		}
		//////////// Printing  VIP ////////////
		else if(TempTruck->getTruck_type() == 'V')
		{
			cout << TempTruck->getTruck_id();
			cout << "{";
			while(!TempTruck->CargoInisdeTruck.isEmpty())
			{
				TempTruck->CargoInisdeTruck.dequeue(TempCargo);
				cout << TempCargo->getid();
				TempCargoQueue.enqueue(TempCargo,no2);
				no2++;
				if(!TempTruck->CargoInisdeTruck.isEmpty())
					cout << ",";
			}
			cout << "}" << " ";
			no2 = 1;
			while(!TempCargoQueue.isEmpty())
			{
				TempCargoQueue.dequeue(TempCargo);
				TempTruck->CargoInisdeTruck.enqueue(TempCargo,no2);
				no2++;
			}
			TempTruck->CargoInisdeTruck.peekFront(TempCargo);
			Moving_Trucks.enqueue(TempTruck,INT_MAX - (CDT_Calculator(TempCargo,TempTruck)));
		}
	}
	cout<<endl<<"----------------------------------------------------"<<endl;

}

void Company::PrintEmptyTrucks()
{
	Truck* TempTruck;
	cout << Normal_Truck_Empty.getCounter() + VIP_Truck_Empty.getCounter() + Special_Truck_Empty.getCounter();
	cout << " Empty trucks: ";

	//////////// Printing Normal  /////////

	Queue<Truck*> TempNormTruck;
	cout << "[";
	while (!Normal_Truck_Empty.isEmpty())
	{
		Normal_Truck_Empty.dequeue(TempTruck);
		cout << TempTruck->getTruck_id();
		if (!Normal_Truck_Empty.isEmpty())
			cout << ",";
		TempNormTruck.enqueue(TempTruck);
	}
	cout << "] ";
	while (!TempNormTruck.isEmpty())
	{
		TempNormTruck.dequeue(TempTruck);
		Normal_Truck_Empty.enqueue(TempTruck);
	}

	//////////// Printing Special /////////

	Queue<Truck*> TempSpecialTruck;
	cout << "(";
	while (!Special_Truck_Empty.isEmpty())
	{
		Special_Truck_Empty.dequeue(TempTruck);
		cout << TempTruck->getTruck_id();
		if (!Special_Truck_Empty.isEmpty())
			cout << ",";
		TempSpecialTruck.enqueue(TempTruck);
	}
	cout << ") ";
	while (!TempSpecialTruck.isEmpty())
	{
		TempSpecialTruck.dequeue(TempTruck);
		Special_Truck_Empty.enqueue(TempTruck);
	}

	//////////// Printing  VIP ////////////

	Queue<Truck*> TempVIPTruck;
	cout << "{";
	while (!VIP_Truck_Empty.isEmpty())
	{
		VIP_Truck_Empty.dequeue(TempTruck);
		cout << TempTruck->getTruck_id();
		if (!VIP_Truck_Empty.isEmpty())
			cout << ",";
		TempVIPTruck.enqueue(TempTruck);
	}
	cout << "} ";
	while (!TempVIPTruck.isEmpty())
	{
		TempVIPTruck.dequeue(TempTruck);
		VIP_Truck_Empty.enqueue(TempTruck);
	}
	cout << endl;
	cout << "----------------------------------------------------" << endl;
}

void Company::PrintCurrentTimeStep()
{
	cout<<"Current Time (Day:Hour):"<< TimeStep.Day << ":" << TimeStep.hour << endl;
}

void Company::PrintWaitingCargos()
{
	Cargo* TempCargo;
	cout << waiting_Special.getCounter() + waiting_VIP.getCount() + waiting_Normal.getCounter();
	cout << " "<< "Waiting Cargos: ";

	//////////// Printing Normal  /////////

	LinkedList<Cargo*> TempNormal;
	cout << "[";
	while(!waiting_Normal.isEmpty())
	{
		waiting_Normal.DeleteFirst(TempCargo);
		cout << TempCargo->getid();
		if(!waiting_Normal.isEmpty())
			cout << ",";
		TempNormal.InsertBeg(TempCargo);
	}
	cout << "]";
	while(!TempNormal.isEmpty())
	{
		TempNormal.DeleteFirst(TempCargo);
		waiting_Normal.InsertBeg(TempCargo);
	}

	cout << " ";

	//////////// Printing Special /////////

	Queue<Cargo*> TempSpecial;
	cout << "(";
	while(!waiting_Special.isEmpty())
	{
		waiting_Special.dequeue(TempCargo);
		cout << TempCargo->getid();
		if(!waiting_Special.isEmpty())
			cout << ",";
		TempSpecial.enqueue(TempCargo);
	}
	cout << ")";
	while(!TempSpecial.isEmpty())
	{
		TempSpecial.dequeue(TempCargo);
		waiting_Special.enqueue(TempCargo);
	} 

	cout << " ";

	//////////// Printing  VIP ////////////

	PriorityQueue<Cargo*> TempVIP;
	cout << "{";
	while(!waiting_VIP.isEmpty())
	{
		waiting_VIP.dequeue(TempCargo);
		cout << TempCargo->getid();
		if(!waiting_VIP.isEmpty())
			cout << ",";
		TempVIP.enqueue(TempCargo,PriorityEquation(TempCargo));
	}
	cout << "}" << endl;
	while(!TempVIP.isEmpty())
	{
		TempVIP.dequeue(TempCargo);
		waiting_VIP.enqueue(TempCargo,PriorityEquation(TempCargo));
	}

	cout<<"----------------------------------------------------"<<endl;

}

void Company::PrintDeliveredCargos()
{
	Cargo* TempCargo;
	Queue<Cargo*> TempQueue;
	cout << Delivered_Cargo.getCounter();
	cout << " "<< "Delivered Cargos: ";

	while(!Delivered_Cargo.isEmpty())
	{
		Delivered_Cargo.dequeue(TempCargo);
		if(TempCargo->getCargoType() == 'N')
			cout << "["  << TempCargo->getid() << "] ";
		else if(TempCargo->getCargoType() == 'V')
			cout << "{"  << TempCargo->getid() << "} ";
		else if(TempCargo->getCargoType() == 'S')
			cout << "("  << TempCargo->getid() << ") ";
		TempQueue.enqueue(TempCargo);
	}
	while(!TempQueue.isEmpty())
	{
		TempQueue.dequeue(TempCargo);
		Delivered_Cargo.enqueue(TempCargo);
	}

	cout << endl;
	cout<<"----------------------------------------------------"<<endl;

}

void Company::PrintInCheckupTrucks()
{

	cout << Normal_CheckUp.getCounter() + VIP_CheckUp.getCounter() + Special_CheckUp.getCounter();
	cout << " " << "In-Checkup Trucks: ";

	Truck* TR;
	Queue<Truck*> Temp;
	cout << "[";
	while(!Normal_CheckUp.isEmpty())
	{
		Normal_CheckUp.dequeue(TR);
		cout << TR->getTruck_id();
		if(!Normal_CheckUp.isEmpty())
			cout << ",";
		Temp.enqueue(TR);
	}
	cout << "]";
	while(!Temp.isEmpty())
	{
		Temp.dequeue(TR);
		Normal_CheckUp.enqueue(TR);
	}

	cout << " ";

	//////////// Printing Special /////////

	cout << "(";
	while(!Special_CheckUp.isEmpty())
	{
		Special_CheckUp.dequeue(TR);
		cout << TR->getTruck_id();
		if(!Special_CheckUp.isEmpty())
			cout << ",";
		Temp.enqueue(TR);
	}
	cout << ")";
	while(!Temp.isEmpty())
	{
		Temp.dequeue(TR);
		Special_CheckUp.enqueue(TR);
	} 

	cout << " ";

	//////////// Printing  VIP ////////////

	cout << "{";
	while(!VIP_CheckUp.isEmpty())
	{
		VIP_CheckUp.dequeue(TR);
		cout << TR->getTruck_id();
		if(!VIP_CheckUp.isEmpty())
			cout << ",";
		Temp.enqueue(TR);
	}
	cout << "}" << endl;
	while(!Temp.isEmpty())
	{
		Temp.dequeue(TR);
		VIP_CheckUp.enqueue(TR);
	}

	cout<<"----------------------------------------------------"<<endl;
}

/////////////////////////////////////////// Events Functions //////////////////////////////////////

void Company:: Prepare(Cargo* newCargo)
{
	if(newCargo->getCargoType() == 'N')
		waiting_Normal.InsertEnd(newCargo);
	else if(newCargo->getCargoType() == 'S')
		waiting_Special.enqueue(newCargo);
	else if(newCargo->getCargoType() == 'V')
		waiting_VIP.enqueue(newCargo , PriorityEquation(newCargo));
}

void Company:: Cancel(int id)
{
	Cargo* cancelcargo = waiting_Normal.CancelCargoFromList(id);
	delete cancelcargo;
	cancelcargo = nullptr;
}

void Company:: Prompt(int id, int extraMoney)
{
	Cargo* promotedlcargo = waiting_Normal.CancelCargoFromList(id);


	if (promotedlcargo != nullptr)
	{
		promotedlcargo->setCost( promotedlcargo->getCost() + extraMoney);
		promotedlcargo->setCargoType('V');
		waiting_VIP.enqueue(promotedlcargo , PriorityEquation(promotedlcargo) );
	}
}

Company::~Company()
{
}

///////////////////////////////////////////////////////////////////////////////////////


