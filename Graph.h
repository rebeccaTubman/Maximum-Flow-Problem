#pragma warning(disable: 4996)
using namespace std;

#include <iostream>
#include "List.h"

#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
private:
	// Properties
	int** Capacity;
	int sizeV, sizeE;
	bool GIsValid;

	// Ptivate Methods

	// Return true if num is in the range [1,max].
	bool InRange(int num, int max);

public:
	// C'tor Method
	Graph(int V, int E);
	// Copy C'tor Method
	Graph(Graph* G);
	// D'tor
	~Graph();

	// Public Methods

	// Makes an empty graph with V vertices.
	void MakeEmptyGraph(int V);

	// Returns true if the edge (u,v) in E. Otherwise, returns false.
	bool IsAdjacent(int u, int v) const;

	// Sets |V| (size of vertices set) to be newV.
	void setSizeV(int newV);
	// Sets |E| (size of edges set) to be newE.
	void setSizeE(int newE);
	// Sets the capacity (weight) of (u,v) to be newCapacity.
	void setEdgeCapacity(int u, int v, int newCapasity);
	// Sets GIsValid.
	void setGIsValid(bool valid);

	// Returns a singly linked list of which vertices u is adjacent to (in ascending order).
	List* GetAdjList(int u) const;
	// Returns the size of set V.
	int getSizeV() const;
	// Returns the size of set E.
	int getSizeE() const;
	// Returns c(u,v) = the capasity of edge (u,v).
	int getEdgeCapacity(int u, int v);
	// Returns GIsValid.
	bool getIsGValid() const;

	// Adds the edge (u,v) with capacity c to the graph. //void 
	bool AddEdge(int u, int v, int c);
	// Removes the edge (u,v) from the graph.
	void RemoveEdge(int u, int v);

	// Overloading the >> Operator. This method reads all the edges of the graph while checking if the graph is a vaild input.
	friend istream& operator>>(istream& file, Graph& G);
};

#endif // GRAPH_H