// program to implement bellman ford algorithm

#include <iostream>
using namespace std;
#define INF 999999
// allocated space for adjacency matrix representation
#define adjacencyMatrixDimension 150

// N -> number of vertices in graph
int N;

void bellmanFord(int adjacencyMatrix[adjacencyMatrixDimension][adjacencyMatrixDimension], int S){
	// input is given in 1 based indexing, and shortest path is calculated using 
	// 0 based indexing
	S--;
	int i, j, k, relaxationOperations, modificationBearingRelaxations;
	int distance[N];

	relaxationOperations = 0;
	modificationBearingRelaxations = 0;

	// used to determine if bellman ford algorithm is applicable
	bool bellmanFordPossible = true;
	// used to determine whether further relax edge operations are required
	bool isRelaxationRequired = true;
	// initialize distances from S to all other vertices as INF
	for(i = 0; i < N; i++){
		distance[i] = INF;
	}

	// distance of source vertex to itself is 0
	distance[S] = 0;

	// relax all edges N-1 times
	for(k = 0; k < N-1; k++){
		if(isRelaxationRequired){
			isRelaxationRequired = false;
			for(i = 0; i < N; i++){
				if(distance[i] != INF){
					relaxationOperations++;
					for(j = 0; j < N; j++){
						if(adjacencyMatrix[i][j] != INF && distance[j] > distance[i] + adjacencyMatrix[i][j]){
							modificationBearingRelaxations++;
							distance[j] = distance[i] + adjacencyMatrix[i][j];
							isRelaxationRequired = true;
						}
					}
				}
			}
		}
		else{
			break;
		}
	}

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			if(adjacencyMatrix[i][j] != INF && distance[i] != INF && distance[j] > distance[i] + adjacencyMatrix[i][j]){
					distance[j] = distance[i] + adjacencyMatrix[i][j];
					bellmanFordPossible = false;
				}
		}
	}

	// if negative weight cycle is present in given graph
	if(!bellmanFordPossible){
		cout << "-1\n";
	}

	else{
		// printing the required solution
		for(i = 0; i < N; i++)
			cout << distance[i] << " ";
		cout << relaxationOperations << " " << modificationBearingRelaxations << "\n";
	}
}

int main(){
	int D, S, i, j;

	// D -> whether graph is directed or not
	// S -> source vertex (1 indexed)
	cout << "Enter the value of N, D, and S\n";
	cin >> N >> D >> S;
	
	int adjacencyMatrix[adjacencyMatrixDimension][adjacencyMatrixDimension];
	
	cout << "Enter the value of adjacency matrix\n";
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			cin >> adjacencyMatrix[i][j];
		}
	}
	
	bellmanFord(adjacencyMatrix, S);

	return 0;
}
