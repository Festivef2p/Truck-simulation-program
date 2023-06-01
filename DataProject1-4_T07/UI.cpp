#include "UI.h"
#include "Company.h"

UI::UI()
{

}

int UI::ModeSelect()
{
	int x;
	cout << "Please select the mode you prefer (1 - interactive 2 - Step by step 3 - Silent): ";
	cin >> x;
	cout << endl;
	return x;
}

char* UI::ReadFileName()
{
	char* name = new char[50];
	cout << "Please Enter The File Name: ";
	cin >> name;
	cin.get();
	cout << endl;
	return name;
}

void UI::Disp_INT(Company* pcomp)
{
	pcomp->PrintCurrentTimeStep();

	pcomp->PrintWaitingCargos();

	pcomp->PrintEmptyTrucks();

	pcomp->PrintMovingCargos();

	pcomp->PrintInCheckupTrucks();

	pcomp->PrintDeliveredCargos();

	cin.get();
}

void UI::Disp_STS(Company* pcomp)
{
	pcomp->PrintCurrentTimeStep();

	pcomp->PrintWaitingCargos();

	pcomp->PrintEmptyTrucks();

	pcomp->PrintMovingCargos();

	pcomp->PrintInCheckupTrucks();

	pcomp->PrintDeliveredCargos();

}

UI::~UI()
{

}