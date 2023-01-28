#pragma once

template <class T>
class Vector
{
	T* ptr;
	int maxElements;
	int nElementCount;

public:

	Vector() : maxElements(16), nElementCount(0)
	{
		ptr = new T[16];
	}

	~Vector() { delete[] ptr; }

	void push(T item)
	{
		if (maxElements == (nElementCount+1))
		{
			maxElements += 16;
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

