/*
Contains implementation of following graph algorithms:
(a) Topological Sorting				(Q = 3)
(b) Dijkstra's algorithm 			(Q = 4)
(c) Bellman Ford Algorithm 			(Q = 5)
(d) Floyd Warshall algorithm 		(Q = 6)

--------------------------------------------------------
Submitted on: 13/12/2017
--------------------------------------------------------

Developed by:
Raghav Sharma
2015EEB1071
--------------------------------------------------------
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>
#define INF 999999
// allocated space for adjacency matrix representation
#define adjacencyMatrixDimension 150
using namespace std;

// N -> number of vertices in graph
int N;

/*****  Topological Sort Algorithm  *****/ 

/*** stack operations ***/
struct stackNode{
	int data;
	struct stackNode *next;
}*stackHead;

struct stackNode *createNewStackNode(int x){
	struct stackNode *newptr = new stackNode;
	newptr->data = x;
	newptr->next = NULL;

	return newptr;
}

void insertStackNode(int x){
	struct stackNode *newptr = createNewStackNode(x);
	if(stackHead == NULL){
		stackHead = newptr;
		return;
	}
	// inserting stackNode at the head of linked list
	newptr->next = stackHead;
	stackHead = newptr;
}

void popFromStack(){
	struct stackNode *temp;
	if(stackHead != NULL){
		temp = stackHead;
		stackHead = stackHead->next;
		free(temp);
	}
}

bool checkIfStackEmpty(){
	if(stackHead == NULL)
		return true;
	else
		return false;
}

int topStack(){
		return stackHead->data;
}

void topologicalSortUtil(int v, bool visited[], int adjacencyMatrix[adjacencyMatrixDimension][adjacencyMatrixDimension]){
	int i;
	// mark the current node as visited
	visited[v] = true;

	// recur for all vertices adjacent to this vertex
	for(i = N-1; i >= 0; i--){
		if(adjacencyMatrix[v][i] == 1 && !visited[i]){
			topologicalSortUtil(i, visited, adjacencyMatrix);
		}
	}

	insertStackNode(v);
}

void topologicalSort(int adjacencyMatrix[adjacencyMatrixDimension][adjacencyMatrixDimension]){
	stackHead = NULL;
	// keeps track of visited nodes during topological sort
	bool visited[N];
	int i, j, k, startNode;
	startNode = -1;

	// initially, mark all vertices as not visited
	for(i = 0; i < N; i++){
		visited[i] = false;
	}

	for(k = 0; k < N; k++){

		// startNode contains the parent node of topological sort
		for(i = N-1; i >= 0; i--){
			for(j = 0; j < N; j++){
				if(adjacencyMatrix[j][i] == 0 && visited[i] == false){
					startNode = j;
				}
				else{
					startNode = -1;
					break;
				}
			}
			if(startNode != -1){
				topologicalSortUtil(i, visited, adjacencyMatrix);
			}
		}
	}

	while(!checkIfStackEmpty()){
		cout << topStack() + 1 << " ";
		popFromStack();
	}
	cout << "\n";
}

bool checkIfCyclicUtil(int v, bool visited[], bool recursionStack[N], int adjacencyMatrix[adjacencyMatrixDimension][adjacencyMatrixDimension]){
	int i, j;

	if(visited[v] == false){
		// mark current node as visited and part of recursion stack
		visited[v] = true;
		recursionStack[v] = true;

		// recur for all vertices adjacent to this vertex
		for(i = 0; i < N; i++){
			if(adjacencyMatrix[v][i] == 1){
				if(!visited[i] && checkIfCyclicUtil(i, visited, recursionStack, adjacencyMatrix)){
					return true;
				}
				else if(recursionStack[i]){
					return true;
				}
			}
		}
	}
	// remove the vertex from recursion stack
	recursionStack[v] = false;
	return false;
}

// returns 1 if given graph is cyclic
bool checkIfCyclic(int adjacencyMatrix[adjacencyMatrixDimension][adjacencyMatrixDimension]){
	int i;
	// used for marking all the vertices as not visited and not part of recursion stack
	bool visited[N], recursionStack[N];

	for(i = 0; i < N; i++){
		visited[i] = false;
		recursionStack[i] = false;
	}

	// call recursive helper function to detect cycle in diff DFS trees
	for(i = 0; i < N; i++){
		if(checkIfCyclicUtil(i, visited, recursionStack, adjacencyMatrix)){
			return true;
		}
	}
	return false;
}



/*****  Dijkstras Algorithm  *****/

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


/*****  Bellman Ford Algorithm  *****/

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


/*****  Floyd Warshall Algorithm  *****/  

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
	int T, Q, D, S, i, j, adjacencyMatrix[adjacencyMatrixDimension][adjacencyMatrixDimension];
	cin >> T;
	while(T--){
		cin >> Q;

		if(Q == 1 || Q == 2){
			cin >> N >> D >> S;
			for(i = 0; i < N; i++){
				for(j = 0; j < N; j++){
					cin >> adjacencyMatrix[i][j];
				}
			}
			cout << "Not Implemented!\n";
		}



		// topological sort
		else if(Q == 3){
			clock_t begin = clock();
			cin >> N;
			for(i = 0; i < N; i++){
				for(j = 0; j < N; j++){
					cin >> adjacencyMatrix[i][j];
				}
			}

			// check whether graph is acyclic or not
			if(checkIfCyclic(adjacencyMatrix)){
				cout << "-1\n";
			}

			else{
				topologicalSort(adjacencyMatrix);
			}
			clock_t end = clock();
			printf("Time Elapsed = %.6f\n", double(end-begin)/CLOCKS_PER_SEC);
		}

		// dijkstras algorithm
		else if(Q == 4){
			clock_t begin = clock();
			bool checkIfDijkstraApplicable = true;
			cin >> N >> D >> S;

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
			clock_t end = clock();
			printf("Time Elapsed = %.6f\n", double(end-begin)/CLOCKS_PER_SEC);
		}

		// bellman ford algorithm
		else if(Q == 5){
			clock_t begin = clock();
			cin >> N >> D >> S;
			for(i = 0; i < N; i++){
				for(j = 0; j < N; j++){
					cin >> adjacencyMatrix[i][j];
				}
			}

			bellmanFord(adjacencyMatrix, S);
			clock_t end = clock();
			printf("Time Elapsed = %.6f\n", double(end-begin)/CLOCKS_PER_SEC);
		}

		// floyd warshall algorithm
		else if(Q == 6){
			clock_t begin = clock();
			cin >> N >> D;
			for(i = 0; i < N; i++){
				for(j = 0; j < N; j++){
					cin >> adjacencyMatrix[i][j];
				}
			}

			floydWarshall(adjacencyMatrix);
			clock_t end = clock();
			printf("Time Elapsed = %.6f\n", double(end-begin)/CLOCKS_PER_SEC);
		}

		else{
			cout << "Invalid query type!\n";
		}
	}

	return 0;
}
