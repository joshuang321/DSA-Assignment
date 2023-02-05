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
	struct Iterator
	{
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

	private:
		pointer ptr;
	
	public:
		Iterator(pointer ptr) : ptr(ptr) {}

		reference operator*() const { return *ptr; }
		pointer operator->() { return ptr; }
		Iterator& operator++() { ptr++; return *this; }
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
		friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; };
	};

	Iterator begin()
	{
		if (ptr)
			return Iterator(&ptr[0]);
		else
			return end();
	}

	Iterator end() { return Iterator(&ptr[nElementCount]); }

	Vector() : maxElements(4), nElementCount(0), ptr(NULL)
	{
#if defined (_DEBUG)
		OutputDebugStringA("Vector_DC\n");
#endif
	}

	~Vector() 
	{
		if (ptr)
			delete[] ptr;
	}

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

	Vector& operator=(const Vector&) = default;
	
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

	Vector& operator=(Vector&&) = default;

	T* push(T&& item)
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

	void add(T item)
	{
		if (ptr == NULL)
			ptr = new T[maxElements];
		else if (maxElements == (nElementCount + 1))
		{
			maxElements += 4;
			T* new_ptr = new T[maxElements];

			for (int i = 0; i < nElementCount; i++)
				new_ptr[i] = std::move(ptr[i]);

			delete[] ptr;
			ptr = new_ptr;
		}

		ptr[nElementCount++] = item;
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