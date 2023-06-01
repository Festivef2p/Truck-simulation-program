#pragma once

class Time
{
public:
	int Day;
	int hour;
	Time(int d,int h);
	Time();

	int getDay();
	int getHour();
	void TimeIncDay();
	int ChangetoHoursFormat();
	void ChangetoDayHourForamt(int x);
};