#include "Time.h"


Time::Time(const int Hours, const int Mins)
	:Hours(Hours), Minutes(Mins)
{
		
}

Time::Time()
{
}

int Time::getHours() const
{
	return this->Hours;
}

int Time::getMinutes() const
{
	return this->Minutes;
}

std::ostream& operator<<(std::ostream& of, const Time& time)
{
	of << time.getHours() << ":" << time.getMinutes();
	return of;
}
