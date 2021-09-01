#pragma once
#include "VECTOR.h"


class FileReader
{
public:

	/**
	 * @brief read data from file
	 *
	 * Given a path to the file, reads the file and returns a 2d vector of strings containing the data.
	 *
	 * @param  path - path to the file
	 * @return Vector of vector of strings
	 */
	Vector<Vector<std::string>> readDataFromFile(const std::string& path) const;

	/**
	 * @brief get headers from file
	 *
	 * Reads the header names from csv files.
	 *
	 * @param  path - path to the file
	 * @return Vector of strings
	 */
	Vector<std::string> readColNamesFromFile(const std::string& path)const;



private:

};





