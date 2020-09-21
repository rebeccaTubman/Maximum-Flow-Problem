#include "MaxHeap.h"

// Private Methods

// Returns the index in data that is the left son of node.
int MaxHeap::Left(int node) {
	return ((2 * node) + 1);
}
// Returns the index in data that is the right son of node.
int MaxHeap::Right(int node) {
	return ((2 * node) + 2);
}
// Returns the index in data that is the parent of node.
int MaxHeap::Parent(int node) {
	return ((node - 1) / 2);
}
// Swaps between the elements in index node1 and intex node2. 
void MaxHeap::Swap(int node1, int node2) {
	Node* tmp = data[node1];
	data[node1] = data[node2];
	data[node2] = tmp;
	// update indexes 
	index[data[node1]->getData()] = node1;
	index[data[node2]->getData()] = node2;
}
// Fixes the heap that has node as root.
void MaxHeap::FixHeap(int node) {
	int max;
	int left = Left(node);
	int right = Right(node);

	if (left < heapSize && data[left]->geyKey() > data[node]->geyKey()) {
		max = left;
	}
	else {
		max = node;
	}
	if (right < heapSize && data[right]->geyKey() > data[max]->geyKey()) {
		max = right;
	}
	if (max != node) {
		Swap(node, max);
		FixHeap(max);
	}
}

// C'tor & D'tor Methods

// C'tor Method - empty heap.
MaxHeap::MaxHeap(int size) {
	this->data = new Node *[size];
	this->maxSize = size;
	this->heapSize = 0;
	this->index = new int[size];
}
// C'tor Method - creates heap with the elements (index, key) from the array.
MaxHeap::MaxHeap(int* keys, int size) {
	this->heapSize = this->maxSize = size;
	this->data = new Node *[size];
	this->index = new int[size];
	for (int i = 0; i < size; i++) {
		Node* node = new Node(i, keys[i]);
		this->data[i] = node;
		this->index[i] = i;
	}
	for (int i = size / 2 - 1; i >= 0; i--) {
		FixHeap(i);
	}
}
// D'tor Method
MaxHeap::~MaxHeap() {
	MakeEmpty();
}

// Public Methods

// Removes all the elements in the heap while freeing memory allocated.
void MaxHeap::MakeEmpty() {
	for (int i = 0; i < heapSize; i++) {
		delete data[i];
	}
	delete[] data;
	delete[] index;
	data = NULL;
	index = NULL;
}
// Returns true if the heap is empty. Otherwise, returns false.
bool MaxHeap::IsEmpty() const {
	return (this->heapSize == 0);
}

// Returns the data of the max element stored in the root of the heap.
int MaxHeap::Max() const {
	return this->data[0]->getData();
}
// Removes the max element from the root of the heap and fixes the heap.
int MaxHeap::DeleteMax() {
	if (this->heapSize < 1) {
		cout << "Error: Empty heap\n";
		exit(1);
	}
	Node* maxNode = data[0];
	int max = maxNode->getData();
	delete maxNode;
	heapSize--;
	data[0] = data[this->heapSize];
	FixHeap(0);
	return max;
}
// Adds a new element in the correct position.
void MaxHeap::Insert(int vertex, int key) {
	if (this->heapSize == this->maxSize) {
		cout << "Error: Full Heap\n";
		exit(1);
	}
	Node* item = new Node(vertex, key);
	int i = this->heapSize;
	this->heapSize++;
	// Going up on the tree to inesrt item in the right level
	while ((i > 0) && (data[Parent(i)]->geyKey() < item->geyKey())) {
		this->data[i] = this->data[Parent(i)];
		this->index[data[i]->getData()] = i;
		i = Parent(i);
	}
	this->data[i] = item;
	this->index[vertex] = i;
}
// Updates the key of element where data = vertex and updates the position.
void MaxHeap::IncreaseKey(int vertex, int newKey) {
	int i = index[vertex];
	if (i < this->heapSize) {
		data[i]->setKey(newKey);
		while (i > 0 && this->data[Parent(i)]->geyKey() < this->data[i]->geyKey()) {
			Swap(i, Parent(i));
			i = Parent(i);
		}
	}
}