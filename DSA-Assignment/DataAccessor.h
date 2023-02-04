#pragma once

#include "Vector.h"
#include <fstream>
#include <string>

template <class T, class D=Vector<T>>
class DataAccessor
{
	const char* filename;

protected:
	D cacheData;

	DataAccessor(const char* filename) : filename(filename), cacheData()
	{
		std::ifstream ifDataFile(filename, std::ifstream::in);
		std::string strline;

		while (std::getline(ifDataFile, strline))
			cacheData.push(T(strline));
	}

	~DataAccessor()
	{
		std::ofstream ofDataFile(filename);

		D::template Iterator it = cacheData.begin(),
			endIt = cacheData.end();

		if (it != endIt)
		{
			ofDataFile << *it;
			it++;

			for (auto It = it;
				It != endIt;
				It++)
				ofDataFile << '\n' << *It;
		}
	}

public:
	T* addObject(T&& obj) { return cacheData.push(std::move(obj)); }
	void removeObject(T& obj) { cacheData.pop(obj); }
};