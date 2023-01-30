#pragma once

#include <string>
#include <iostream>
#include <Windows.h>

template <class T>
class Vector
{
	T* ptr;
	int maxElements;
	int nElementCount;

public:

	Vector() : maxElements(4), nElementCount(0)
	{
		ptr = NULL;
	}

	~Vector() 
	{
		if (ptr)
			delete[] ptr;
	}

	void push(T item)
	{
		if (ptr == NULL)
			ptr = new T[maxElements];
		else if (maxElements == (nElementCount+1))
		{
			maxElements += 4;
			T* new_ptr = new T[maxElements];

			memcpy_s(new_ptr, sizeof(T) * maxElements, ptr, sizeof(T) * nElementCount);
			delete[] ptr;
			ptr = new_ptr;
		}

		ptr[nElementCount++] = item;
	}

	void pop(T item)
	{
		if (nElementCount == 0)
			return;

		for (int i=0; i<nElementCount; i++)
		{
			if (item == ptr[i])
			{
				for (int j = i + 1; i < nElementCount; i++)
					ptr[j - 1] = std::move(ptr[j]);
			}
		}

		nElementCount--;
	}

	int count() { return nElementCount; }

	T& operator[](int nIndex) { return ptr[nIndex]; }
};

