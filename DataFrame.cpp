#include "DataFrame.h"

DataFrame::DataFrame()
{
}

DataFrame::DataFrame(const Vector<Vector<std::string>> &recs, const Vector<std::string> &cols)
{
	for (int i = 0; i < recs.size(); ++i)
		this->records.push_back(Record(recs[i]));

	std::cout << "Records Added: " << this->records.size() << std::endl;
	this->colNames = cols;
}

std::size_t DataFrame::size() const
{
	return this->records.size();
}

void DataFrame::appendData(const Vector<Vector<std::string>> &recs)
{
	for (int i = 0; i < recs.size(); ++i)
		this->records.push_back(Record(recs[i]));
}

DataFrame DataFrame::filter(const int month, const int year)
{
	DataFrame df;
	df.colNames = this->colNames;

	for (int i = 0; i < this->records.size(); ++i)
	{
		const auto &curRec = this->records[i];

		auto date = curRec.getDate();

		if (std::stoi(date.GetMonth()) == month && date.GetYear() == year)
			df.records.push_back(curRec);
	}
	return df;
}

DataFrame DataFrame::filter(const int day, const int month, const int year)
{
	DataFrame df;
	df.colNames = this->colNames;

	for (int i = 0; i < this->records.size(); ++i)
	{
		const auto &curRec = this->records[i];

		auto date = curRec.getDate();

		if (std::stoi(date.GetMonth()) == month && date.GetYear() == year && date.GetDay() == day)
			df.records.push_back(curRec);
	}
	return df;
}

DataFrame DataFrame::filter(const int year)
{
	DataFrame df;
	df.colNames = this->colNames;

	for (int i = 0; i < this->records.size(); ++i)
	{
		const auto &curRec = this->records[i];

		auto date = curRec.getDate();

		if (date.GetYear() == year)
			df.records.push_back(curRec);
	}
	return df;
}

int DataFrame::getColIndexByName(const std::string &tar) const
{
	for (int i = 0; i < this->colNames.size(); ++i)
		if (this->colNames[i] == tar)
			return i;
	return -1;
}

void DataFrame::printRows(const std::size_t num) const
{
	for (int i = 0; i < num; i++)
	{
		std::cout << this->records[i] << std::endl;
	}
}

Vector<std::tuple<Date, float>> DataFrame::reduce(std::string colName)
{
	auto curRecord = this->records[0];
	int count = 0;
	float sum = 0;
	int index = getColIndexByName(colName);
	Vector<std::tuple<Date, float>> reduced;

	Date key = curRecord.getDate();
	for (size_t i = 0; i < this->records.size(); i++)
	{
		auto nextRecord = this->records[i];
		auto next_key = nextRecord.getDate();
		if (key != next_key || (i == this->records.size() - 2))
		{
			reduced.push_back(std::make_tuple(key, sum / count));
			sum = 0;
			count = 0;
			key = next_key;
		}

		sum += nextRecord.getData()[index - 1];
		count++;
	}
	return reduced;
}

Vector<std::string> DataFrame::getColNames() const
{
	return this->colNames;
}

void DataFrame::MaxSolarRadiationsOnDate(Date date)
{
	//obtaining all records for Solar activity matching the date
	auto df = filter(date.GetDay(), std::stoi(date.GetMonth()), date.GetYear());

	//relative index of the column containing solar radiation
	constexpr auto require_col = 10;

	//std::map with first key year, second month, third day and the final a bst containing readings
	std::map<int, std::map<int, std::map<int, Bst<float>>>> readings;

	for (const auto &rec : df.records)
	{
		readings[date.GetYear()][std::stoi(date.GetMonth())][date.GetDay()].insertElement(rec.getDataAtIndex(require_col));
	}

	const auto maxReading = readings[date.GetYear()][std::stoi(date.GetMonth())][date.GetDay()].getDatainRInorder()[0];

	Vector<Record> results;
	for (const auto &ins : df.records)
	{
		if (ins.getDataAtIndex(require_col) == maxReading)
			results.push_back(ins);
	}

	std::cout << "Date: " << date.GetDay() << '/' << date.GetMonth() << '/' << date.GetYear() << std::endl;
	std::cout << "High solar radiation for the day: " << maxReading << " W/m2" << std::endl;
	std::cout << endl;
	std::cout << "Time:" << std::endl;
	for (const auto &rec : results)
		std::cout << rec.getTime() << std::endl;
}
