#include "Tools.h"
#include <sstream>
#include <ctime>
#include <iomanip>

#include "Map.h"

namespace Tools
{
	Vector<std::string> split(std::string strline, char delim)
	{
		Vector<std::string> strs;
		size_t ndelim = strline.find(delim);
		while (ndelim != strline.npos)
		{
			strs.push(strline.substr(0, ndelim));
			strline = strline.substr(ndelim + 1, strline.length() - ndelim - 1);
			ndelim = strline.find(delim);
		}
		return strs;
	}

	time_t strToTime(std::string strTime)
	{
		tm _tm;
		std::istringstream(strTime.c_str()) >> std::get_time(&_tm, "%Y-%m-%d %H:%M:%S");
		return std::mktime(&_tm);
	}

	std::string timeToString(time_t time)
	{
		char strBuf[256];
		std::size_t szCount;
		tm _tm;

		localtime_s(&_tm, &time);
		szCount = strftime(strBuf, 256, "%Y-%m-%d %H:%M:%S", &_tm);

		return std::string(strBuf, szCount);
	}
}

namespace Hash
{
	int charvalue(char c)
	{
		if (isalpha(c))
		{
			if (isupper(c))
				return (int)c - (int)'A';
			else
				return (int)c - (int)'a' + 26;
		}
		else
			return -1;
	}
}