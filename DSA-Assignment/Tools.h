#pragma once

#include "Vector.h"
#include <string>

namespace Tools
{
	Vector<std::string> split(std::string strline, char delim);
	time_t strToTime(std::string strTime);
	std::string timeToString(time_t time);
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