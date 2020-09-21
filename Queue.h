#pragma warning(disable: 4996)
using namespace std;

#include <iostream>
#include "List.h"

#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
private:
	// Properties
	List Q;

public:
	// C'tor Method
	Queue();
	// D'tor Method
	~Queue();

	// Public Methods

	// Removes all the elements in the queue while freeing memory allocated.
	void MakeEmpty();
	// Returns true if the queue has only the dummy element (= empty). Otherwise, returns false.
	bool IsEmpty() const;
	// Returns the data in the front of the queue.
	int Front() const;
	// Adds a new element with data v to the end of the queue.
	void Enqueue(int v);
	// Removes the first element from the queue and returns the data. 
	int Dequeue();
};

#endif // QUEUE_H