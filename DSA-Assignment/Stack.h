#pragma once
#include "Post.h"
#include <iostream>

//stack ADT using nodes
class Stack {
private:
	struct Node {
		Post item;
		Node* next;
	};
	Node* topNode;

public:
	Stack();
	~Stack();

	bool push(Post item);
	bool pop();
	bool pop(Post& item);
	void getTop(Post& item);
	bool isEmpty();
};