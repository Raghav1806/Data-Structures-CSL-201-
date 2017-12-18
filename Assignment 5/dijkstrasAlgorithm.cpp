// program for implementing dijkstra's shortest path algorithm

#include <iostream>
using namespace std;
#define INF 999999
// allocated space for adjacency matrix representation
#define adjacencyMatrixDimension 150

// N -> number of vertices in graph
int N;

// returns vertex with minimum distance value, from the set of vertices which
// are not yet included in shortest path tree
int findMinDistance(int distance[], bool shortestPathTreeSet[]){
	int min = INF;
	int minIndex, i;
	for(i = 0; i < N; i++){
		if(shortestPathTreeSet[i] == false && distance[i] <= min){
			min = distance[i];
			minIndex = i;
		}
	}

	return minIndex;
}

// function to implement dijkstra's single source shortest path algorithm using 
// adjacency matrix representation
void dijkstra(int adjacencyMatrix[adjacencyMatrixDimension][adjacencyMatrixDimension], int S){
	// input is given in 1 based indexing, and shortest path is calculated using 
	// 0 based indexing
	S--;

	int i, j, nearest;

	// holds the shortest distance from source vertex to each vertex
	int distance[N];

	// shortestPathTreeSet[i] will be true if vertex i+1 (indexed 1) is included 
	// in shortest path tree
	bool shortestPathTreeSet[N];

	// initializing all distances as INF and shortestPathTreeSet[i] as false
	for(i = 0; i < N; i++){
		distance[i] = INF;
		shortestPathTreeSet[i] = false;
	}

	// distance of source vertex from itself is always 0
	distance[S] = 0;

	// finding shortest path for all vertices
	for(i = 0; i < N; i++){
		// find the min distance vertex from the set of vertices not processed 
		nearest = findMinDistance(distance, shortestPathTreeSet);

		// mark the picked vertex as processed
		shortestPathTreeSet[nearest] = true;

		// update distance[] value of adjacent vertices of the picked vertex
		for(j = 0; j < N; j++){
			// update the value of distance[j] iff:
			// (a) It is not in shortestPathTreeSet[]
			// (b) There is an edge from nearest to j
			// (c) distance[nearest] + adjacencyMatrix[nearest][j] < distance[j]

			if((!shortestPathTreeSet[j]) && (adjacencyMatrix[nearest][j] != INF) && (distance[nearest] != INF) && (distance[nearest] + adjacencyMatrix[nearest][j] < distance[j]))
				distance[j] = distance[nearest] + adjacencyMatrix[nearest][j];
		}
	}

	// printing the solution
	for(i = 0; i < N; i++){
		cout << distance[i] << " ";
	}
	cout << "\n";
}

int main(){
	int D, S, i, j;
	bool checkIfDijkstraApplicable;
	checkIfDijkstraApplicable = true;

	// D -> whether graph is directed or not
	// S -> source vertex (1 indexed)
	cout << "Enter the value of N, D, and S\n";
	cin >> N >> D >> S;
	
	int adjacencyMatrix[adjacencyMatrixDimension][adjacencyMatrixDimension];
	
	cout << "Enter the value of adjacency matrix\n";
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			cin >> adjacencyMatrix[i][j];
			if(adjacencyMatrix[i][j] < 0){
				checkIfDijkstraApplicable = false;
			}
		}
	}
	if(!checkIfDijkstraApplicable){
		cout << "-1\n";
	}
	else{
		dijkstra(adjacencyMatrix, S);
	}
	return 0;
}
