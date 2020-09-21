#include "Graph.h"

// Ptivate Methods

// Return true if num is in the range [1,max].
bool Graph::InRange(int num, int max) {
	if (num < 1 || num > max) {
		return false;
	}
	return true;
}

// C'tor & D'tor Methods

// C'tor Method
Graph::Graph(int V, int E) {
	sizeE = E;
	sizeV = V;
	GIsValid = true;
	MakeEmptyGraph(V);
}
// Copy C'tor Method
Graph::Graph(Graph* G) {
	sizeE = G->getSizeE();
	sizeV = G->getSizeV();
	GIsValid = G->getIsGValid();

	// Make a duplicate of G's Capasity
	Capacity = new int*[sizeV];

	for (int i = 0; i < sizeV; i++) {
		Capacity[i] = new int[sizeV];
		for (int j = 0; j < sizeV; j++) {
			Capacity[i][j] = G->getEdgeCapacity(i, j);
		}
	}
}
// D'tor
Graph::~Graph() {
	for (int i = 0; i < sizeV; i++) {
		delete[] Capacity[i];
	}
	delete[] Capacity;
}

// Public Methods

// Makes an empty graph with V vertices.
void Graph::MakeEmptyGraph(int V) {
	Capacity = new int*[sizeV];
	for (int i = 0; i < sizeV; i++) {
		Capacity[i] = new int[sizeV];
		for (int j = 0; j < sizeV; j++) {
			Capacity[i][j] = 0;
		}
	}
}

// Returns true if the edge (u,v) in E. Otherwise, returns false.
bool Graph::IsAdjacent(int u, int v) const {
	return (Capacity[u][v] != 0);
}

// Sets |V| (size of vertices set) to be newV.
void Graph::setSizeV(int newV) {
	this->sizeV = newV;
}
// Sets |E| (size of edges set) to be newE.
void Graph::setSizeE(int newE) {
	this->sizeE = newE;
}
// Sets the capacity (weight) of (u,v) to be newCapacity.
void Graph::setEdgeCapacity(int u, int v, int newCapasity) {
	Capacity[u][v] = newCapasity;
}
// Sets GIsValid.
void Graph::setGIsValid(bool valid) {
	this->GIsValid = valid;
}

// Returns a singly linked list of which vertices u is adjacent to (in ascending order).
List* Graph::GetAdjList(int u) const {
	List* Adj = new List();
	Node* curr = NULL;
	for (int i = 0; i < sizeV; i++) {
		if (IsAdjacent(u, i)) {
			Adj->InsertAfter(curr, i);
			curr = Adj->Last();
		}
	}
	return Adj;
}
// Returns the size of set V.
int Graph::getSizeV() const {
	return sizeV;
}
// Returns the size of set E.
int Graph::getSizeE() const {
	return sizeE;
}
// Returns c(u,v) = the capasity of edge (u,v).
int Graph::getEdgeCapacity(int u, int v) {
	return Capacity[u][v];
}
// Returns GIsValid.
bool Graph::getIsGValid() const {
	return GIsValid;
}

// Adds the edge (u,v) with capacity c to the graph.
bool Graph::AddEdge(int u, int v, int c) {
	if (!IsAdjacent(u, v) && u != v) {
		Capacity[u][v] = c;
		sizeE++;
		return true;
	}
	return false;
}
// Removes the edge (u,v) from the graph.
void Graph::RemoveEdge(int u, int v) {
	Capacity[u][v] = 0;
	sizeE--;
}

// Overloading the >> Operator. This method reads all the edges of the graph while checking if the graph is a vaild input.
istream& operator>>(istream& file, Graph& G) {
	int u, v, c;
	bool status = true;
	while (!file.eof() && status) {
		u = v = c = INT_MIN;
		file >> u >> v >> c;
		// Read empty lines - the input given was in range and is a simple Graph.
		if (u == INT_MIN) {
			break;
		}
		// Invalid line - one or more inputs are missing.
		if (v == INT_MIN || c == INT_MIN) {
			status = false;
			break;
		}
		// Checks if vertices u and v are in the range [1,|V|] & c > 0
		if (G.InRange(u, G.getSizeV()) && G.InRange(v, G.getSizeV()) && c > 0) {
			// Checks if the input is a simple Graph -> The graph has no graph loops or multiple edges.
			status = G.AddEdge(u - 1, v - 1, c);
		}
		else {
			// The input was out of range. 
			// Hence, stop the loop with condition 'status' and let the program know the input was invalid.
			status = false;
		}
	}
	if (!status) {
		G.setGIsValid(false);
	}
	return file;
}