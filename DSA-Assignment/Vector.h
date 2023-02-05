//==================================================================
// Student Number : S10205140B, S10223630K
// Student Name :Joshua Ng, Armirola Roseller Iii Tumolva
// Module Group : P03
//==================================================================

#pragma once

#include <string>
#include <iostream>
#include <Windows.h>

/* Generized dynamic array for storing objects */
template <class T>
class Vector
{
	T* ptr;
	int maxElements;
	int nElementCount;

public:
	struct Iterator
	{
		/* Iterator to be used to DataAccessor, and only used as a forward iterator */
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

	private:
		pointer ptr;
	
	public:
		Iterator(pointer ptr) : ptr(ptr) {}

		/* For dereferencing to get the current object of the current position in the data structure */
		reference operator*() const { return *ptr; }
		/* For dereferencing through arrow operator */
		pointer operator->() { return ptr; }
		/* For using arithmetic on the Iterator */
		Iterator& operator++() { ptr++; return *this; }
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
		/* Used for comparing Iterator positions */
		friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; };
	};

	/* Gets the starting element of the data structure, returns the end if it is empty */
	Iterator begin()
	{
		if (nElementCount > 0)
			return Iterator(&ptr[0]);
		else
			return end();
	}

	/* Indicate the end of the array */
	Iterator end() { return Iterator(&ptr[nElementCount]); }

	/* Constructor */
	Vector() : maxElements(4), nElementCount(0), ptr(NULL)
	{
#if defined (_DEBUG)
		OutputDebugStringA("Vector_DC\n");
#endif
	}

	/* Destructor */
	~Vector() 
	{
		if (ptr)
			delete[] ptr;
	}

	/* Copy Constructor, used for copying */
	Vector(const Vector& vec)
	{
#if defined (_DEBUG)
		OutputDebugStringA("Vector_CC\n");
#endif
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

	/* Copy Assignment Constructor, used for situation like, vec1 = vec2 */
	Vector& operator=(const Vector& vec)
	{
		if (ptr)
			delete[] ptr;
		ptr = NULL;
		/* Copies the contents if it is not empty */
		if (vec.ptr)
		{
			ptr = new T[vec.maxElements];
			for (int i = 0; i < vec.nElementCount; i++)
				ptr[i] = T(vec.ptr[i]);
		}

		maxElements = vec.maxElements;
		nElementCount = vec.nElementCount;
		return *this;
	}
	
	/* Move Constructor */
	Vector(Vector&& vec)
	{
#if defined (_DEBUG)
		OutputDebugStringA("Vector_MC\n");
#endif
		ptr = vec.ptr;
		maxElements = vec.maxElements;
		nElementCount = vec.nElementCount;
		
		vec.ptr = NULL;
		vec.maxElements = 4;
		vec.nElementCount = 0;
	}

	/* Default Move Constructor */
	Vector& operator=(Vector&&) = default;

	/* Pushes the object into the data structure at the back */
	T* push(T&& item)
	{
		/* Allocates the memory if not allocated yet */
		if (ptr == NULL)
			ptr = new T[maxElements];
		else if (maxElements == (nElementCount+1))
		{
			maxElements += 4;
			T* new_ptr = new T[maxElements];

			/* Move the object to into the new memory location */
			for (int i = 0; i < nElementCount; i++)
				new_ptr[i] = std::move(ptr[i]);

			delete[] ptr;
			ptr = new_ptr;
		}

		ptr[nElementCount++] = std::move(item);
		return &ptr[nElementCount - 1];
	}

	/* Pops the first object equivalent to the referenced object */
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

	/* returns the number of elements in the data structure */
	int count() { return nElementCount; }

	/* returns the element at nIndex position */
	T& operator[](int nIndex) { return ptr[nIndex]; }
};