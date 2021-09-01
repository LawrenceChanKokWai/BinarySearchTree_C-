// DATE.CPP - Date class implementation

#include <string>
#include "DATE.h"
#include "Util.h"

Date::Date()
{
	day = -1;
	month = "-1";
	year = -1;
}

Date::Date(int d, string m, int y)
{
	day = d;
	month = m;
	year = y;
}

istream &operator>>(istream &input, Date &D)
{
	input >> D.day >> D.month >> D.year;
	return input;
}

ostream &operator<<(ostream &os, const Date &D)
{
	os << get_month_string(std::stoi(D.month)) << " " << D.year;
	return os;
}

bool Date::operator!=(const Date &D)
{
	if (this->month != D.month || this->year != D.year)
		return true;
	return false;
}

unsigned Date::GetDay() const
{
	return day;
}

void Date::SetDay(unsigned d)
{
	day = d;
}

string Date::GetMonth()
{
	return month;
}

void Date::SetMonth(string m)
{
	month = m;
}

unsigned Date::GetYear() const
{
	return year;
}

void Date::SetYear(unsigned y)
{
	year = y;
}

bool Date::operator<(const Date &rhs) const
{
	return (std::to_string(day) + std::to_string(year) + month) <
		   (std::to_string(rhs.day) + std::to_string(rhs.year) + rhs.month);
}

bool Date::operator>(const Date &rhs) const
{
	return (std::to_string(day) + std::to_string(year) + month) >
		   (std::to_string(rhs.day) + std::to_string(rhs.year) + rhs.month);
}

bool Date::operator==(const Date &rhs) const
{
	return (std::to_string(day) + std::to_string(year) + month) ==
		   (std::to_string(rhs.day) + std::to_string(rhs.year) + rhs.month);
}


std::string Date::to_string() const
{
	return (std::to_string(day) +"-" + month +"-" + std::to_string(year));
}
