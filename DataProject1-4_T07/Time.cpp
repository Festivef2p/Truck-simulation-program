#include"Time.h"

Time::Time(int d,int h)
{
	Day = d;
	hour = h;
}

Time::Time()
{
	Day = 0;
	hour = 0;
}

int Time:: getDay()
{
	return Day;
}

int Time:: getHour()
{
	return hour;
}

void Time::TimeIncDay()
{
	if (hour == 24)
	{
		Day++;
		hour = 0;
	}
}

int Time::ChangetoHoursFormat()
{
	return Day*24 + hour;
}

void Time::ChangetoDayHourForamt(int x)
{
	Day = x/24;
	hour = x%24;
}