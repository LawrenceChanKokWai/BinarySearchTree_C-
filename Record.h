#pragma once


#include "VECTOR.h"
#include "DATE.h"
#include "Time.h"
#include<iostream>

class Record
{
public:

	Record(const Vector<std::string>& row);
	Record();

	Date getDate() const;
	Time getTime() const;

	Vector<float> getData() const;

	/**
	 * @brief update the record at a given index
	 *
	 * Access the data of the record and update it at the given index with the newVal.
	 *
	 * @param  index - to be updated
	 * @param  newVal - the new value to insert at the index
	 * @return void
	 */
	void updateDataAtIndex(const int index,const double newVal);

	bool operator <(Record &rhs) ;
	bool operator >(Record &rhs) ;

	bool operator <(Record &rhs) const ;
	bool operator >(Record &rhs) const ;

	bool operator <(const Record &rhs) const;
	bool operator >(const Record &rhs) const;

	bool operator <(const Record &rhs) ;
	bool operator >(const Record &rhs) ;


	float getDataAtIndex(const int loc) const;

private:
	Date date;
	Time time;
	Vector<float> data;

	
};

std::ostream& operator << (std::ostream& of, const Record& rec);