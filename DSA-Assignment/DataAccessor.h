#pragma once

#include "Vector.h"
#include <fstream>
#include <string>

template <class T>
class DataAccessor
{
	const char* filename;

protected:
	Vector<T> cacheData;

	DataAccessor<T>(const char* filename) : filename(filename), cacheData()
	{
		std::ifstream ifDataFile(filename, std::ifstream::in);
		std::string strline;

		while (std::getline(ifDataFile, strline))
			cacheData.push(T(strline));
	}

	~DataAccessor<T>()
	{
		std::ofstream ofDataFile(filename);

		if (cacheData.count() != 0)
			ofDataFile << cacheData[0];

		for (int i = 1; i < cacheData.count(); i++)
			ofDataFile << '\n' << cacheData[i];
	}

public:
	void addObject(T obj) { cacheData.push(obj); }
	void removeObject(T obj) { cacheData.pop(obj); }
};