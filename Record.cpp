#include "Record.h"
#include <string>
#include "Util.h"
#include <iostream>
#include <algorithm>

Record::Record(const Vector<std::string> &row)
{
	const auto dateTime = tokenizer(row[0], ' ');
	if (dateTime.size() == 2)
	{

		const auto date = tokenizer(dateTime[0], '/');
		const auto t = tokenizer(dateTime[1], ':');

		auto is_number = [](const std::string &s) {
			return !s.empty() && std::find_if(s.begin(),
											  s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
		};

		if (date.size() == 3 && t.size() == 2)
		{
			this->date = Date(std::stoi(date[0]), date[1], std::stoi(date[2]));
			this->time = Time(std::stoi(t[0]), std::stoi(t[1]));
			for (std::size_t i = 1; i < row.size(); i++)
			{

				const auto tarData = is_number(row[i]) ? std::stoi(row[i]) : 0;
				// std::cout <<"<<"<<row[i]<<">>\n";
				this->data.push_back(tarData);
			}
		}
	}
}

Record::Record()
{
}

Date Record::getDate() const
{
	return this->date;
}

Time Record::getTime() const
{
	return this->time;
}

Vector<float> Record::getData() const
{
	return this->data;
}

void Record::updateDataAtIndex(const int index, const double newVal)
{
	this->data[index] = newVal;
}

std::ostream &operator<<(std::ostream &of, const Record &rec)
{
	const char *delim = "<>";
	of << rec.getDate() << delim << rec.getTime() << delim;

	for (int i = 0; i < rec.getData().size(); ++i)
		of << rec.getData()[i] << delim;

	return of;
}

bool Record::operator<(Record &rhs)
{
	if (data.size() && rhs.data.size())
	{
		return this->data[0] < rhs.data[0];
	}
	return false;
}

bool Record::operator>(Record &rhs)
{
	if (data.size() && rhs.data.size())
	{
		return this->data[0] > rhs.data[0];
	}
	return false;
}

bool Record::operator<(Record &rhs) const
{
	if (data.size() && rhs.data.size())
	{
		return this->data[0] < rhs.data[0];
	}
	return false;
}

bool Record::operator>(Record &rhs) const
{
	if (data.size() && rhs.data.size())
	{
		return this->data[0] > rhs.data[0];
	}
	return false;
}

bool Record::operator<(const Record &rhs) const
{
	if (data.size() && rhs.data.size())
	{
		return this->data[0] < rhs.data[0];
	}
	return false;
}

bool Record::operator>(const Record &rhs) const
{
	if (data.size() && rhs.data.size())
	{
		return this->data[0] > rhs.data[0];
	}
	return false;
}

float Record::getDataAtIndex(const int loc) const
{
	if (this->data.size() < loc)
	{
		std::cout << "date not available" << std::endl;
		return 0.0f;
	}
	return this->data[loc];
}