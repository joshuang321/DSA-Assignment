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
	Stack()
	{
		Stack<T>::Node* tempNode = topNode;

		while (tempNode)
		{
			topNode = tempNode->next;
			delete tempNode;
			tempNode = topNode;
		}
	}

	~Stack()
	{
		Stack<T>::Node* tempNode = topNode;

		while (tempNode)
		{
			topNode = tempNode->next;
			delete tempNode;
			tempNode = topNode;
		}
	}

	bool push(T item)
	{
		if (topNode)
		{
			Stack<T>::Node* tempNode = new Stack<T>::Node;

			if (tempNode)
			{
				tempNode->item = item;
				tempNode->next = topNode;
				topNode = tempNode;
				return true;
			}
		}
		else
		{
			topNode = new Stack<T>::Node;
			if (topNode)
			{
				topNode->item = item;
				return true;
			}
		}

		return false;
	}

	bool pop()
	{
		if (!topNode)
			return false;

		Stack<T>::Node* tempNode = topNode;
		topNode = tempNode->next;
		delete topNode;

		return true;
	}

	bool pop(T& item)
	{
		if (!topNode)
			return false;

		Stack<T>::Node* tempNode = topNode;
		topNode = tempNode->next;
		delete topNode;

		return true;
	}


	void getTop(T& item)
	{
		if (!topNode)
			return false;

		Stack<T>::Node* tempNode = topNode;
		topNode = tempNode->next;
		item = topNode->item;
		delete topNode;

		return true;
	}

	bool isEmpty()
	{
		return !topNode;
	}
};