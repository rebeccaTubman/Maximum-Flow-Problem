#pragma warning(disable: 4996)
using namespace std;

#include <iostream>
#include "Node.h"

#ifndef LIST_H
#define LIST_H

class List
{
private:
	// Properties
	Node *head, *tail;
	int size;

	// Private Methods

	// Finds and returns the parent of the node that has his data as the data given.
	Node* Parent(int data) const;

public:
	// C'tor Method
	List();
	// D'tor Method
	~List();

	// Public Methods

	// Makes an empty list.
	void MakeEmpty();

	// Returns true if the list is empty. Otherwise, returns false.
	bool IsEmpty() const;

	// Returns the head of the list.
	Node* First() const;
	// Reutrns the tail of the list.
	Node* Last() const;
	// Returns the size (number of nodes) of the list.
	int getSize() const;

	// Adds a new node to the list after a given node.
	void InsertAfter(Node* curr, int vertex);
	// Finds the wanted node in the list.
	Node* Find(int node) const;
	// Deletes the node after curr from the list and returns the data.
	int DeleteAfter(Node* curr);
	// Deletes the node from the list.
	bool DeleteNode(int node);
};

#endif // LIST_H