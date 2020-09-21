# Maximum-Flow-Problem
Solves the maximum-flow problem in flow networks using the Ford-Fulkerson algorithm.
Implemented BFS and Dijkstra methods for the improving paths.
The project was programmed using C++ in VS 2017.

Instructions:
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

