//==================================================================
// Student Number : S10205140B, S10223630K
// Student Name :Joshua Ng, Armirola Roseller Iii Tumolva
// Module Group : P03
//==================================================================

#pragma once

#include "Vector.h"
#include <string>

namespace Tools
{
	/* Used by classes to split the string into an array of strings using a delimeter */
	Vector<std::string> split(std::string strline, char delim);

	/* Convert string to time */
	time_t strToTime(std::string strTime);

	/* Convert time to string */
	std::string timeToString(time_t time);

	/* Applies a selection sort on the Vector using a comparison function */
	template <class T>
	void selectionSort(Vector<T>& vec, bool (*cmp_func)(T&, T&))
	{
		for (int i = 0; i < vec.count(); i++)
		{
			int min_index = i;

			for (int j = i + 1; j < vec.count(); j++)
			{
				if (cmp_func(vec[j], vec[min_index]))
					min_index = j;
			}

			T data = vec[i];
			vec[i] = vec[min_index];
			vec[min_index] = data;
		}
	}
}

namespace Hash
{
	int charvalue(char c);

	/* Hashes the string using polynomial rolling function, given a hashsize */
	template<int HashSize>
	int hash(std::string& strKey)
	{
		int hash = strKey[0];

		for (int i = 1;
			i < strKey.length();
			i++) {

			hash *= 52;
			hash += charvalue(strKey[i]);
			/* Chops the data to prevent overflow */
			hash &= 0xFFFF;
		}
		return hash % HashSize;
	}
}