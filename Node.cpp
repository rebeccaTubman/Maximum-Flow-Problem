#include "Node.h"

// C'tor & D'tor Methods

// C'tor Method - empty node.
Node::Node() {
	next = NULL;
}
// C'tor Method -creates node with the given input.
Node::Node(int data, int key, Node* next) {
	this->data = data;
	this->key = key;
	this->next = next;
}
// D'tor Methods
Node::~Node() {

}

// Public Methods

// Returns the data.
int Node::getData() const {
	return this->data;
}
// Returns the key.
int Node::geyKey() const {
	return this->key;
}
// Returns the next node.
Node* Node::getNext() const {
	return this->next;
}

// Sets the data to newData.
void Node::setData(int newData) {
	this->data = newData;
}
// Sets the key to newKey.
void Node::setKey(int newKey) {
	this->key = newKey;
}
// Sets the next node to newNext.
void Node::setNext(Node* newNext) {
	this->next = newNext;
}

// Insert newNode after current node.
void Node::InsertAfter(Node* node) {
	node->next = this->next;
	this->next = node;
}
// Delete node after current node
Node* Node::DeleteAfter() {
	if (!this->next)
		return NULL;
	Node* tmp = this->next;
	this->next = tmp->next;
	return tmp;
}