

#pragma once
#include "VECTOR.h"
#include "Record.h"
#include "BinarySearchTree.h"
#include <queue>
#include <tuple>
#include <vector>
#include <map>
class DataFrame
{
public:

	DataFrame();

	DataFrame(const Vector<Vector<std::string>> &records, const Vector<std::string> &cols);

	std::size_t size() const;

	/**
	* @brief  Appends miscellaneous records in the dataframe
	*		
	*	Appends records into the dataframe store; used for reading files
	*	separately from the constructor.
	*
	* @param  records - vector of records
	* @return void
	*/

	void appendData(const Vector<Vector<std::string>> &records);

	/**
	 * @brief  filters records according to specified month and year
	 *
	 * Goes through the records in the DataFrame one by one
	 * matching the month and year with the provided args, 
	 * and then returns a new DataFrame object with only those records.
	 *
	 * @param  month - month of the year
	 * @param  year -  year
	 * @return DataFrame
	 */
	DataFrame filter(const int month, const int year); // returns all records having same year and month

	/**
	 * @brief  filters records according to specified day, month and year
	 *
	 * Goes through the records in the DataFrame one by one
	 * matching the day, month and year with the provided args, 
	 * and then returns a new DataFrame object with only those records.
	 * @param  day - day of the year
	 * @param  month - month of the year
	 * @param  year -  year
	 * @return DataFrame
	 */
	DataFrame filter(const int day, const int month, const int year); 

	/**
	 * @brief  filters records according to specified month and year
	 *
	 * Overload of function above; filters records according to year only
	 * returns a new DataFrame with records from only that year.
	 *
	 * @param  year -  year
	 * @return DataFrame
	 */
	DataFrame filter(const int year); //returns all records having same year

	/**
	 * @brief  filters records according to a condition 
	 *
	 * Overload of previous filters; calls the callable on every entry of the column 
	 * specified in a record then returns a new DataFrame containing only those entries
	 * which returned true according to the callable.
	 *
	 * @param  colName - name of the column to filter
	 * @param  callable - a boolean function encoding a condition
	 * @return DataFrame
	 */
	template <typename Callable>
	DataFrame filter(const std::string &colName, Callable callable);

	/**
	 * @brief  transforms a column of the records
	 *
	 * Applies the transformation in callable to the entries in colName column of the records.
	 *
	 * @param  colName - name of the column to transform
	 * @param  callable - any callable transformation (accepts and returns double)
	 * @return DataFrame
	 */
	template <typename Callable>
	DataFrame map(const std::string &colName, Callable callable); //

	/**
	 * @brief  compute averages for each month (or only one)
	 *
	 * Takes a column name, and goes through that column checking for a key (month and year)
	 * Returns average computed for that key. If there are multiple keys, returns averages for all.
	 *
	 * @param  colName - column name to average
	 * @return Vector of tuples containing Date as key, and a float as average
	 */
	Vector<std::tuple<Date, float>> reduce(std::string colName);

	/**
	 * @brief get column index by its name
	 *
	 * Returns the index of a column given the column name.
	 *
	 * @param  colName - column name to average
	 * @return int
	 */
	int getColIndexByName(const std::string &) const;

	/**
	 * @brief prints specified rows of the dataframe for debugging purposes
	 *
	 * Prints num number of rows of the records in the DataFrame.
	 *
	 * @param  num - integer denoting number of rows to print.
	 * @return void
	 */
	
	/**
	* @brief  Finds maximum solar radiation times for a given day
	*		
	*	Filters all the record for the given date, finds the maximum solar radiation value using binary search tree
	*	and returns prints all those times with the equivalent solar radiation activity
	*
	* @param  date - date
	* @return void
	*/
	void MaxSolarRadiationsOnDate(Date date);

	void printRows(const std::size_t num = 10) const;

	Vector<std::string> getColNames() const;

private:
	Vector<Record> records;
	Vector<std::string> colNames;
};

template <typename Callable>
inline DataFrame DataFrame::filter(const std::string &col, Callable callable)
{
	DataFrame df;
	df.colNames = this->colNames;

	int index = this->getColIndexByName(col);
	if (index > 1)
	{
		for (int i = 0; i < this->records.size(); ++i)
		{
			auto curRec = this->records[i];

			if (callable(curRec.getData()[index - 1]))
				df.records.push_back(curRec);
		}
	}
	return df;
}

template <typename Callable>
inline DataFrame DataFrame::map(const std::string &colName, Callable callable)
{
	int index = this->getColIndexByName(colName);
	if (index == -1)
		throw std::runtime_error("Invalid Column Name Specified");

	DataFrame df;
	df.colNames = this->colNames;
	if (index > 1)
	{

		for (int i = 0; i < this->records.size(); ++i)
		{
			auto curRec = this->records[i];

			if (curRec.getData().size() >= 16)
			{
				int offsetIndex = index - 1;
				curRec.updateDataAtIndex(offsetIndex, callable(curRec.getData()[offsetIndex]));
				df.records.push_back(curRec);
			}
		}
	}
	return df;
}
