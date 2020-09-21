#pragma warning(disable: 4996)
using namespace std;

#include <iostream>
#include "Node.h"

#ifndef MAXHEAP_H
#define MAXHEAP_H

class MaxHeap
{
private:
	// Properties
	Node** data;
	int* index;
	int maxSize;
	int heapSize;

	// Private Methods

	// Returns the index in data that is the left son of node.
	static int Left(int node);
	// Returns the index in data that is the right son of node.
	static int Right(int node);
	// Returns the index in data that is the parent of node.
	static int Parent(int node);
	// Swaps between the elements in index node1 and intex node2. 
	void Swap(int node1, int node2);
	// Fixes the heap that has node as root.
	void FixHeap(int node);

public:
	// C'tor Method - empty heap.
	MaxHeap(int size);
	// C'tor Method - creates heap with the elements (index, key) from the array.
	MaxHeap(int* keys, int size);
	// D'tor Method
	~MaxHeap();

	// Public Methods

	// Removes all the elements in the heap while freeing memory allocated.
	void MakeEmpty();
	// Returns true if the heap is empty. Otherwise, returns false.
	bool IsEmpty() const;

	// Returns the data of the max element stored in the root of the heap.
	int Max() const;
	// Removes the max element from the root of the heap and fixes the heap.
	int DeleteMax();
	// Adds a new element in the correct position.
	void Insert(int vertex, int key);
	// Updates the key of element where data = vertex and updates the position.
	void IncreaseKey(int vertex, int newKey);
};

#endif // MAXHEAP_H