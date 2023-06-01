#pragma once

class Company;

class UI
{
	
public:

 	UI();

	int ModeSelect();

	char* ReadFileName();

	void Disp_INT(Company* pcomp);
	void Disp_STS(Company* pcomp);

	~UI();
};

