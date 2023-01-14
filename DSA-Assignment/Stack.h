#pragma once
#include "Post.h"
#include <iostream>

//stack ADT using nodes

template <class T>
class Stack {
private:
	struct Node {
		T item;
		Stack<T>::Node* next;

		Node() : next(NULL) { }
	};
	Stack<T>::Node* topNode;

public:
	Stack();
	~Stack();

	bool push(T item);
	bool pop();
	bool pop(T& item);
	void getTop(T& item);
	bool isEmpty();
	bool sort(bool (*cmp_func)(T& item1, T& item2));
};