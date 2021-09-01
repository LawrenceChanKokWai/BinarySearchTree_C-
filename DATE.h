// DATE.H - Course class definition
// author KRI
// modified smr

#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string> // C++ string library

using namespace std;

class Date
{
public:
	Date();
	Date(int date, string month, int year);
	// Construct a Date from a day/month/year,
	// and number of credits.

	unsigned GetDay() const;
	// Get the number of day.

	void SetDay(unsigned day);
	// Set the number of day.

	string GetMonth();
	// Get the number of month.

	void SetMonth(string month);
	// Set the number of month.

	unsigned GetYear() const;
	// Get the number of year.

	void SetYear(unsigned year);
	// Set the number of year.

	bool operator!=(const Date &D);

	// These operators have been made friends. They have
	// privileged access to class internals.
	// Very useful for debugging the class, but not very good for class design.
	// We will keep using it for now but you will have a chance in a later lab
	// to redesign this class.
	friend ostream &operator<<(ostream &os, const Date &D);
	friend istream &operator>>(istream &input, Date &D);

	bool operator<(const Date &rhs) const;
	bool operator>(const Date &rhs) const;
	bool operator==(const Date &rhs) const;
	
	std::string to_string() const;

private:
	int day;	  // Date of the month
	string month; // Name of the month
	int year;	  // year
};

#endif
