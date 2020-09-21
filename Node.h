#pragma warning(disable: 4996)
using namespace std;

#include <iostream>
#include <stdlib.h>

#ifndef NODE_H
#define NODE_H

class Node
{
private:
	// Properties
	int data, key;
	Node* next;

public:
	// C'tor Method - empty node.
	Node();
	// C'tor Method -creates node with the given input.
	Node(int data, int key = 0, Node* next = NULL);
	// D'tor Methods
	~Node();

	// Public Methods

	// Returns the data.
	int getData() const;
	// Returns the key.
	int geyKey() const;
	// Returns the next node.
	Node* getNext() const;

	// Sets the data to newData.
	void setData(int newData);
	// Sets the key to newKey.
	void setKey(int newKey);
	// Sets the next node to newNext.
	void setNext(Node* newNext);

	// Insert newNode after current node.
	void InsertAfter(Node* newNode);
	// Delete node after current node
	Node* DeleteAfter();
};

#endif // NODE_H