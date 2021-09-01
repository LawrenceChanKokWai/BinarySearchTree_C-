#pragma once

#include "VECTOR.h"

class DataFrame;

	/**
	 * @brief tokenize a string given the delimiter
	 *
	 * Splits a given string as per the provided delimiter.
	 *
	 * @param  str - template for any string type data.
	 * @param delim - template for any char type token.
	 * @return Vector of str
	 */

template<typename _str,typename _delim>
Vector<_str> tokenizer(_str str, const _delim& delim)
{
    Vector<_str> tokens;

    for (auto pos = str.find(delim); pos != std::string::npos; pos = str.find(delim))
    {
        tokens.push_back(str.substr(0, pos));
        str = str.substr(pos + 1);
    }
    tokens.push_back(str);
    return tokens;
}


	/**
	 * @brief returns a month name given its number
	 *
	 * Return a string name of the month given the number. For example, January if given 1, February if 2, etc.
	 *
	 * @param  month - integer representation of month
	 * @return string
	 */
static std::string get_month_string(const int& month)
{
	switch (month)
	{
	case 1: return "January";
	case 2: return "February";
	case 3: return "March";
	case 4: return "April";
	case 5: return "May";
	case 6: return "June";
	case 7: return "July";
	case 8: return "August";
	case 9: return "September";
	case 10: return "October";
	case 11: return "November";
	case 12: return "December";
	default: return "";
	}
}
