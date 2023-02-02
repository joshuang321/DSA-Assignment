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

	Vector(const Vector& vec)
	{
		ptr = NULL;
		if (vec.ptr)
		{
			ptr = new T[vec.maxElements];
			for (int i = 0; i < vec.nElementCount; i++)
				ptr[i] = T(vec.ptr[i]);
		}

		maxElements = vec.maxElements;
		nElementCount = vec.nElementCount;
	}

	Vector& operator=(const Vector&) = default;
	
	Vector(Vector&& vec)
	{
		ptr = vec.ptr;
		maxElements = vec.maxElements;
		nElementCount = vec.nElementCount;
		
		ptr = NULL;
		vec.maxElements = 4;
		vec.nElementCount = 0;
	}

	T* push(T item)
	{
		if (ptr == NULL)
			ptr = new T[maxElements];
		else if (maxElements == (nElementCount+1))
		{
			maxElements += 4;
			T* new_ptr = new T[maxElements];

			for (int i = 0; i < nElementCount; i++)
				new_ptr[i] = std::move(ptr[i]);

			delete[] ptr;
			ptr = new_ptr;
		}

		ptr[nElementCount++] = std::move(item);
		return &ptr[nElementCount - 1];
	}

	void pop(T& item)
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