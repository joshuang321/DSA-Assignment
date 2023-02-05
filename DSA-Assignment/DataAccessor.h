//==================================================================
// Student Number : S10205140B, S10223630K
// Student Name :Joshua Ng, Armirola Roseller Iii Tumolva
// Module Group : P03
//==================================================================

#pragma once

#include "Vector.h"
#include <fstream>
#include <string>

/* Used to read and write the file once using class T as the type, and D as the storage type. Vector is used by default as D */
template <class T, class D=Vector<T>>
class DataAccessor
{
	const char* filename;

protected:
	D cacheData;

	/* Read the file and store the data when constructed */
	DataAccessor(const char* filename) : filename(filename), cacheData()
	{
		std::ifstream ifDataFile(filename, std::ifstream::in);
		std::string strline;

		while (std::getline(ifDataFile, strline))
			cacheData.push(T(strline));
	}

	/* Write to the file when destructed */
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
	/* Uses the push and pop to add and remove objects from persistent data */
	T* addObject(T&& obj) { return cacheData.push(std::move(obj)); }
	void removeObject(T& obj) { cacheData.pop(obj); }
};