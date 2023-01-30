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

	int count() { return nElementCount; }

	T& operator[](int nIndex) { return ptr[nIndex]; }
};

