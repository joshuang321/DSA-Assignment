#include "Stack.h"

template <class T>
Stack<T>::Stack()
{
	topNode = NULL;
}

template <class T>
Stack<T>::~Stack()
{
	Stack<T>::Node* tempNode = topNode;

	while (tempNode)
	{
		topNode = tempNode->next;
		delete tempNode;
		tempNode = topNode;
	}
}

template <class T>
bool Stack<T>::push(T item)
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

template <class T>
bool Stack<T>::pop()
{
	if (!topNode)
		return false;

	Stack<T>::Node* tempNode = topNode;
	topNode = tempNode->next;
	delete topNode;

	return true;
}

template <class T>
bool Stack<T>::pop(T& item)
{
	if (!topNode)
		return false;

	Stack<T>::Node* tempNode = topNode;
	topNode = tempNode->next;
	item = topNode->item;
	delete topNode;

	return true;
}

template <class T>
void Stack<T>::getTop(T& item)
{
	item = topNode->item;
}

template <class T>
bool Stack<T>::isEmpty()
{
	return !topNode;
}

template <class T>
bool Stack<T>::sort(bool (*cmp_func)(T& item1, T& item2))
{
	// do insertion sort or something ..
	// call function ptr like this: cmp_func(item1, item1)
}