#include "FileReader.h"

#include <fstream>
#include <string>
#include "Util.h"

using std::ifstream;
using std::string;

Vector<Vector<std::string>> FileReader::readDataFromFile(const std::string &path) const
{
	ifstream inFile(path);

	if (inFile.is_open())
	{
		Vector<Vector<string>> data;
		bool flag = true;
		string line;
		while (inFile)
		{
			std::getline(inFile, line);
			const auto tokens = tokenizer(line, ','); // obtaining all cols values
			if (flag)
			{
				flag = false;
				continue;
			}
			data.push_back(tokens);
		}
		return data;
	}

	return Vector<Vector<string>>();
}

Vector<std::string> FileReader::readColNamesFromFile(const std::string &path) const
{
	ifstream inFile(path);

	if (inFile.is_open())
	{
		string line;
		std::getline(inFile, line);
		return tokenizer(line, ','); // obtaining all cols values. column names here
	}
	return Vector<string>();
}



/*

std::vector<int> AB = A;
AB.insert(AB.end(), B.begin(), B.end());

*/