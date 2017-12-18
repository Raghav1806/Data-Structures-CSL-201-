// program for implementing floyd warshall algorithm

#include <iostream>
using namespace std;
#define INF 999999
// allocated space for adjacency matrix representation
#define adjacencyMatrixDimension 150

// N -> number of vertices in graph
int N;

// function solves all pair shortest path problem using floyd warshall algorithm
void floydWarshall(int adjacencyMatrix[adjacencyMatrixDimension][adjacencyMatrixDimension]){
	// distance will be the output matrix that will have shortest distance between
	// every pair of vertices
	int distance[adjacencyMatrixDimension][adjacencyMatrixDimension];
	int i, j, k;
	// determines whether floyd warshall algorithm is applicable in given graph
	bool isFloydWarshallApplicable = true;

	// initialize distance[][] matrix same as input adjacency matrix
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			distance[i][j] = adjacencyMatrix[i][j];
		}
	}

	// selecting all vertices as intermediate vertices one by one
	for(k = 0; k < N; k++){
		// selecting all vertices as source one by one
		for(i = 0; i < N; i++){
			// selecting all vertices as destination one by one
			for(j = 0; j < N; j++){
				// if k is an intermediate vertex in path from i to j, update the 
				// value of distance[i][j]
					if(distance[i][j] > distance[i][k] + distance[k][j]){
						distance[i][j] = distance[i][k] + distance[k][j];
				}
			}
		}
	}

	// loop to determine whether floyd warshall algorithm is applicable or not
	for(k = 0; k < N; k++){
		// selecting all vertices as source one by one
		for(i = 0; i < N; i++){
			// selecting all vertices as destination one by one
			for(j = 0; j < N; j++){
				// if k is an intermediate vertex in path from i to j, update the 
				// value of distance[i][j]
					if(distance[i][j] > distance[i][k] + distance[k][j]){
						isFloydWarshallApplicable = false;
				}
			}
		}
	}

	if(isFloydWarshallApplicable){
		// printing the solution 2D matrix
		for(i = 0; i < N; i++){
			for(j = 0; j < N; j++){
				cout << distance[i][j] << " ";
			}
		cout << "\n";
		}
	}

	else{
		cout << "-1\n";
	}
}

int main(){
	int D, i, j;

	// D -> whether graph is directed or not
	cout << "Enter the value of N and D\n";
	cin >> N >> D;
	
	int adjacencyMatrix[adjacencyMatrixDimension][adjacencyMatrixDimension];
	
	cout << "Enter the value of adjacency matrix\n";
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			cin >> adjacencyMatrix[i][j];
		}
	}
	floydWarshall(adjacencyMatrix);
	return 0;
}
