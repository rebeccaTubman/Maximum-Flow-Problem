#include "List.h"

// Private Methods

// Finds and returns the parent of the node that has his data as the data given.
Node* List::Parent(int data) const {
	Node* parent;
	// If the list is empty or the wanted node is the head there is no parent.
	if (IsEmpty() || head->getData() == data) {
		return NULL;
	}
	// Finds the parent of node starting with head.
	else {
		parent = head;
		while (parent && parent->getNext()->getData() != data) {
			parent = parent->getNext();
		}
	}
	return parent;
}

// C'tor & D'tor Methods

// C'tor Method
List::List() {
	MakeEmpty();
}
// D'tor Method
List::~List() {
	while (!IsEmpty()) {
		Node* tmp = this->head;
		this->head = head->getNext();
		delete tmp;
	}
	this->tail = NULL;
}

// Public Methods

// Makes an empty list.
void List::MakeEmpty() {
	this->head = this->tail = NULL;
	this->size = 0;
}

// Returns true if the list is empty. Otherwise, returns false.
bool List::IsEmpty() const {
	return (this->head == NULL);
}

// Returns the head of the list.
Node* List::First() const {
	return this->head;
}
// Reutrns the tail of the list.
Node* List::Last() const {
	return this->tail;
}
// Returns the size (number of nodes) of the list.
int List::getSize() const {
	return this->size;
}

// Adds a new node to the list after a given node.
void List::InsertAfter(Node* curr, int vertex) {
	Node* tmp = new Node(vertex);
	if (!IsEmpty() && !curr) {
		cout << "Error! No node was given.\n";
		return;
	}
	else if (IsEmpty()) {
		head = tail = tmp;
	}
	else {
		tmp->setNext(curr->getNext());
		curr->setNext(tmp);
		if (curr == tail) {
			tail = tmp;
		}
	}
	this->size++;
}
// Finds and returns the wanted node.
Node* List::Find(int node) const {
	if (IsEmpty()) {
		return NULL;
	}
	else if (head->getData() == node) {
		return head;
	}
	Node* parent = Parent(node);
	if (parent) {
		return parent->getNext();
	}
	return NULL;
}
// Deletes the node after curr from the list and returns the data.
int List::DeleteAfter(Node* curr) {
	Node* tmp = curr->getNext();
	int res = tmp->getData();
	curr->setNext(tmp->getNext());
	if (tmp == tail) {
		tail = curr;
	}
	delete tmp;
	this->size--;
	return res;
}
// Deletes the node from the list.
bool List::DeleteNode(int node) {
	Node* tmp;
	if (IsEmpty()) {
		return false;
	}
	else if (head->getData() == node) {
		tmp = head;
		head = tmp->getNext();
		delete tmp;
		this->size--;
		return true;
	}
	else {
		Node* parent = Parent(node);
		if (parent) {
			DeleteAfter(parent);
			return true;
		}
		return false;
	}
}
