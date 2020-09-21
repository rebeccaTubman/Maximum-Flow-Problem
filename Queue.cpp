#include "Queue.h"

// C'tor & D'tor Methods

// C'tor Method
Queue::Queue() {
	MakeEmpty();
}
// D'tor Method
Queue::~Queue() {

}

// Public Methods

// Creates an empty queue
void Queue::MakeEmpty() {
	Q.InsertAfter(NULL, 0);
}
// Returns true if the queue has only the dummy element (= empty). Otherwise, returns false.
bool Queue::IsEmpty() const {
	return (Q.getSize() == 1);
}
// Returns the data in the front of the queue.
int Queue::Front() const {
	if (IsEmpty()) {
		cout << "ERROR: Queue is empty!\n";
		exit(1);
	}
	return Q.First()->getNext()->getData();
}
// Adds a new element with data v to the end of the queue.
void Queue::Enqueue(int v) {
	Q.InsertAfter(Q.Last(), v);
}
// Removes the first element from the queue and returns the data. 
int Queue::Dequeue() {
	if (IsEmpty()) {
		cout << "ERROR: Queue is empty!\n";
		exit(1);
	}
	return Q.DeleteAfter(Q.First());
}