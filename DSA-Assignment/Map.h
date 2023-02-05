//==================================================================
// Student Number : S10205140B, S10223630K
// Student Name :Joshua Ng, Armirola Roseller Iii Tumolva
// Module Group : P03
//==================================================================

#pragma once

#include <string>
#include "Tools.h"

const int  HASH_SIZE = 37;

template<class K, class V>
class Map
{


protected:
	struct Node
	{
		V value;
		K key;
		Node* next;

		Node() :
			next(NULL)
		{ }

		Node(K key) :
			next(NULL),
			key(key)
		{ }

		Node(const Node& node) :
			key(node.key),
			value(node.value),
			next(NULL)
		{ }
	};
private:
	Node* items[HASH_SIZE];

protected:
	Map()
	{
		for (int i = 0; i < HASH_SIZE; i++)
		{
			items[i] = NULL;
		}
	}

	~Map()
	{
		for (int i = 0; i < HASH_SIZE; i++)
		{
			if (items[i])
			{
				Node* temp = items[i];
				while (temp)
				{
					items[i] = temp->next;
					delete temp;
					temp = items[i];
				}
			}
		}
	}

	Map(const Map& map)
	{
		for (int i = 0; i < HASH_SIZE; i++)
		{
			if (map.items[i])
			{
				Node* temp = map.items[i],
					** currentNode = &items[i];
				while (temp)
				{
					*currentNode = new Node(*temp);
					currentNode = &(*currentNode)->next;
					temp = temp->next;
				}
			}
			else
			{
				items[i] = NULL;
			}
		}
	}

	Map & operator=(const Map & map) = default;
	
	Map(Map&& map)
	{
		for (int i = 0; i < HASH_SIZE; i++)
		{
			items[i] = map.items[i];
			map.items[i] = NULL;
		}
	}

	Node* push(K key)
	{
		int hashIndex = Hash::hash<HASH_SIZE>(key);

		if (items[hashIndex])
		{
			Node* temp = items[hashIndex];
			while (temp->next)
				temp = temp->next;
			temp->next = new Node(key);
			return temp;
		}
		items[hashIndex] = new Node(key);
		return items[hashIndex];
	}

	void pop(K key, V& item)
	{
		int hashIndex = Hash::hash<HASH_SIZE>(key);
		
		if (items[hashIndex])
		{
			if (items[hashIndex]->value == item)
			{
				Node* temp = items[hashIndex]->next;
				delete items[hashIndex];
				items[hashIndex] = temp;
			}
			else
			{
				Node* temp = items[hashIndex];
				while (temp->next)
				{
					if (temp->next->value == item)
					{
						Node* tempp = temp->next->next;
						delete temp->next;
						temp->next = tempp;
						break;
					}
					temp = temp->next;
				}
			}
		}
	}

public:
	bool get(K key, V*& item)
	{
		int hashIndex = Hash::hash<HASH_SIZE>(key);

		if (items[hashIndex])
		{
			if (items[hashIndex]->key == key)
			{
				item = &items[hashIndex]->value;
				return true;
			}
			else
			{
				Node* temp = items[hashIndex];
				while (temp->next)
				{
					if (temp->next->key == key)
					{
						item = &temp->next->value;
						return true;
					}
					temp = temp->next;
				}
			}
		}
		return false;
	}

	bool exists(K& key)
	{
		int hashIndex = Hash::hash<HASH_SIZE>(key);

		if (items[hashIndex])
		{
			if (items[hashIndex]->key == key)
			{
				return true;
			}
			else
			{
				Node* temp = items[hashIndex];
				while (temp->next)
				{
					if (temp->next->key == key)
					{
						return true;
					}
					temp = temp->next;
				}
			}
			return false;
		}
		return false;
	}

	struct Iterator
	{
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = V;
		using pointer = V*;
		using reference = V&;

	private:
		Node* pCurNode, **ppBaseNode, **ppEndNode;

	public:
		Iterator(Node** ppNode, Node** ppEndNode) :
			ppBaseNode(ppNode),
			pCurNode(*ppNode),
			ppEndNode(ppEndNode)
		{ }

		reference operator*() const { return pCurNode->value; }
		pointer operator->() { return &pCurNode->value; }
		Iterator& operator++() 
		{
			if (pCurNode->next)
			{
				pCurNode = pCurNode->next;
			}
			else
			{
				if (ppBaseNode != ppEndNode)
				{
					ppBaseNode++;
					while (!*ppBaseNode && ppBaseNode != ppEndNode)
						ppBaseNode++;

					pCurNode = *ppBaseNode;
				}
			}
			return *this;
		}
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
		friend bool operator== (const Iterator& a, const Iterator& b) { return a.pCurNode == b.pCurNode; };
		friend bool operator!= (const Iterator& a, const Iterator& b){ return a.pCurNode != b.pCurNode; };
	};

	Iterator begin()
	{
		for (int i = 0; i < HASH_SIZE; i++)
		{
			if (items[i])
				return Iterator(&items[i], &items[HASH_SIZE]);
		}
		return end();
	}

	Iterator end()
	{
		return Iterator(&items[HASH_SIZE], &items[HASH_SIZE]);
	}
};