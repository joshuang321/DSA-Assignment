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
	Vector<std::string> split(std::string strline, char delim);
	time_t strToTime(std::string strTime);
	std::string timeToString(time_t time);

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

	template<int HashSize>
	int hash(std::string& strKey)
	{
		int hash = strKey[0];

		for (int i = 1;
			i < strKey.length();
			i++) {

			hash *= 52;
			hash += charvalue(strKey[i]);
			hash &= 0xFFFF;
		}
		return hash % HashSize;
	}
}