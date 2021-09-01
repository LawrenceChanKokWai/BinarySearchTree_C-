#pragma once

#include<iostream>
class Time
{
public:
	Time(const int Hours, const int Mins);
	Time();

	int getHours() const;
	int getMinutes() const;

	

private:
	int Hours, Minutes;
};

std::ostream& operator <<(std::ostream& of, const Time& time);





