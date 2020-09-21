#pragma warning(disable: 4996)
using namespace std;

#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <fstream>

#include "Graph.h"
#include "Queue.h"
#include "MaxHeap.h"
#include "List.h"

int V = 0;
int sizeS = 0;

// Instructions:
/*
expected to recive an argument representing file name.
The given file should include a simple graph in the following format:
V // Number of vertices V > 0
E // Number of edges E > 0
s // Source in range [1,V]
t // Sink in range [1,V]
Exactly E group of three numbers: u v c // u,v in range [1,V] and c > 0
* White spaces, new lines and tabs will not matter.

Example for valid graph format in file:
6
			10
1


6
1      2 16
1 3 13
2 3 10
3 2 4

2 4 12
4 3 9
3 5 14
5 4
7
5 6 4

		4 6 20

*/

// Declarations

// Reads from file the size of V and E, the source and sink and validates the input.
bool GetInitialInforamtion(ifstream& file, int& m, int& s, int& t);
// Returns true if num is in the range [1,max].
bool InRange(int num, int max);
// Returns the maximum flow found in the flow network using BFS.
int FordFulkersonBFS(Graph* G, int s, int t, int* S, int* T, int& iterations);
// Returns true if a path from vertex s to t exists. Otherwise, returns false
bool BFS(Graph& G, int s, int t, int* parent, int* d);
// Returns the maximum flow found in the flow network using Dijkstra.
int FordFulkersonGreedy(Graph* G, int s, int t, int* S, int* T, int& iterations);
// Returns true if a path from vertex s to t exists. Otherwise, returns false.
bool Dijkstra(Graph& G, int s, int t, int* parent, int* d);
// Creates the cuts of the flow network.
void MinCut(Graph& G, int* S, int* T, int s, int t, int* parent, int* d);
// Prints the results.
void OutputResult(int maxFlow, int iterations, int* S, int* T);
// Prints the vertices of a given cut (array).
void PrintCut(int* A, int sizeA);


// Main
int main(int argc, char** argv) {
	int iterations = 0, maxFlow, E, s, t;
	int *S = NULL, *T = NULL;
	Graph* G = NULL;

	if (argc <= 1) {
		cout << "No file name entered. Exiting...\n";
		return -1;
	}

	ifstream infile(argv[1]);
	if (infile.is_open() && infile.good()) {
		if (GetInitialInforamtion(infile, E, s, t)) {
			G = new Graph(V, 0);
			infile >> (*G);
		}
		infile.close();
	}
	else {
		cout << "Failed to open file. Exiting...\n";
		exit(1);
	}

	if (G && G->getSizeE() == E && G->getIsGValid()) {
		S = new int[V];
		T = new int[V];

		maxFlow = FordFulkersonBFS(G, s - 1, t - 1, S, T, iterations);
		cout << "BFS Method:\n";
		OutputResult(maxFlow, iterations, S, T);

		iterations = 0;
		sizeS = 0;
		maxFlow = FordFulkersonGreedy(G, s - 1, t - 1, S, T, iterations);
		cout << "Greedy Method:\n";
		OutputResult(maxFlow, iterations, S, T);

		delete[] S;
		delete[] T;
	}
	else {
		cout << "Invalid input\n";
		exit(1);
	}

	if (G) {
		delete G;
	}
	return 0;
}

// Reads from file the size of V and E, the source and sink and validates the input.
bool GetInitialInforamtion(ifstream& file, int& m, int& s, int& t) {
	int n;
	file >> n >> m >> s >> t;
	file.ignore();
	if (!InRange(n, n) || !InRange(m, m) || !InRange(s, n) || !InRange(t, n) || s == t) {
		return false;
	}
	V = n;
	return true;
}
// Returns true if num is in the range [1,max].
bool InRange(int num, int max) {
	if (num<1 || num>max) {
		return false;
	}
	return true;
}

// Returns the maximum flow found in the flow network using BFS.
int FordFulkersonBFS(Graph* G, int s, int t, int* S, int* T, int& iterations) {
	Graph Gf(G);

	int* parent = new int[V];
	int* d = new int[V];
	int u, v, maxflow = 0;

	// Main Loop
	while (BFS(Gf, s, t, parent, d)) {
		int pathflow = INT_MAX;
		// Loop to find the minimum capasity in the path found in the BFS.
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			pathflow = min(pathflow, Gf.getEdgeCapacity(u, v));
		}
		// Updating the capasity in the residual flow graph.
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			Gf.setEdgeCapacity(u, v, Gf.getEdgeCapacity(u, v) - pathflow);
			Gf.setEdgeCapacity(v, u, Gf.getEdgeCapacity(v, u) + pathflow);
		}
		maxflow += pathflow;
		iterations++;
	}

	MinCut(Gf, S, T, s, t, parent, d);

	// Clearing Dynamicly created data.
	delete[] parent;
	delete[] d;

	return maxflow;
}
// Returns true if a path from vertex s to t exists. Otherwise, returns false
bool BFS(Graph& G, int s, int t, int* parent, int* d) {
	Queue Q;
	int u, v, i, sizeAdj;
	List* adj;

	// Init
	for (i = 0; i < V; i++) {
		d[i] = INT_MAX;
		parent[i] = -1;
	}
	d[s] = 0;
	Q.Enqueue(s);

	// Main Loop
	while (!Q.IsEmpty()) {
		u = Q.Dequeue();
		adj = G.GetAdjList(u);
		Node* curr = adj->First();
		sizeAdj = adj->getSize();
		for (i = 0; i < sizeAdj; i++) {
			v = curr->getData();
			if (d[v] == INT_MAX) {
				d[v] = d[u] + 1;
				parent[v] = u;
				Q.Enqueue(v);
			}
			curr = curr->getNext();
		}
		delete adj;
	}
	return (d[t] != INT_MAX); // if the BFS visited in t d[t] will be the shortest path from s to t and not INT_MAX.
}

// Returns the maximum flow found in the flow network using Dijkstra.
int FordFulkersonGreedy(Graph* G, int s, int t, int* S, int* T, int& iterations) {
	Graph Gf(G);

	int* parent = new int[V];
	int* d = new int[V];
	int u, v, maxflow = 0;

	while (Dijkstra(Gf, s, t, parent, d)) {
		int pathflow = INT_MAX;
		// d[t] holds the capasity of the path found.
		pathflow = d[t];
		// Updating the capasity in the residual flow graph.
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			Gf.setEdgeCapacity(u, v, Gf.getEdgeCapacity(u, v) - pathflow);
			Gf.setEdgeCapacity(v, u, Gf.getEdgeCapacity(v, u) + pathflow);
		}
		maxflow += pathflow;
		iterations++;
	}

	MinCut(Gf, S, T, s, t, parent, d);

	// Clearing Dynamicly created data.
	delete[] parent;
	delete[] d;

	return maxflow;
}
// Returns true if a path from vertex s to t exists. Otherwise, returns false
bool Dijkstra(Graph& G, int s, int t, int* parent, int* d) {
	int u, v, i, sizeAdj, w;
	List* adj;

	// Init
	for (i = 0; i < V; i++) {
		d[i] = INT_MIN;
		parent[i] = -1;
	}
	d[s] = INT_MAX;

	MaxHeap Q(d, V);

	// Main Loop
	while (!Q.IsEmpty()) {
		u = Q.DeleteMax();
		adj = G.GetAdjList(u);
		Node* curr = adj->First();
		sizeAdj = adj->getSize();
		for (i = 0; i < sizeAdj; i++) {
			v = curr->getData();
			// Relax
			w = G.getEdgeCapacity(u, v);
			if (d[v] < min(d[u], w)) {
				d[v] = min(d[u], w);
				parent[v] = u;
				Q.IncreaseKey(v, d[v]);
			}
			curr = curr->getNext();
		}
		delete adj;
	}
	return (d[t] != INT_MIN);
}

// Creates the cuts of the flow network.
void MinCut(Graph& G, int* S, int* T, int s, int t, int* parent, int* d) {
	int i, j = 0;
	BFS(G, s, t, parent, d);
	for (i = 0; i < V; i++) {
		if (d[i] != INT_MAX) {
			S[sizeS] = i;
			sizeS++;
		}
		else {
			T[j] = i;
			j++;
		}
	}
}

// Prints the results.
void OutputResult(int maxFlow, int iterations, int* S, int* T) {
	cout << "Max flow = " << maxFlow << endl;
	cout << "Min cut: S = ";
	PrintCut(S, sizeS);
	cout << ". T = ";
	PrintCut(T, V - sizeS);
	cout << endl << "Number of iterations = " << iterations << endl;
}
// Prints the vertices of a given cut (array).
void PrintCut(int* A, int sizeA) {
	for (int i = 0; i < sizeA - 1; i++) {
		cout << (A[i] + 1) << ", ";
	}
	cout << (A[sizeA - 1] + 1);
}