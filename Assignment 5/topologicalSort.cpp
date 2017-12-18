// program to find lexicographically smallest topological sort

#include <iostream>
#include <cstdlib>
using namespace std;
#define INF 999999
// allocated space for adjacency matrix representation
#define adjacencyMatrixDimension 150

// N -> number of vertices in graph
int N;

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

void topologicalSortUtil(int v, bool visited[N], int adjacencyMatrix[adjacencyMatrixDimension][adjacencyMatrixDimension]){
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

bool checkIfCyclicUtil(int v, bool visited[N], bool recursionStack[N], int adjacencyMatrix[adjacencyMatrixDimension][adjacencyMatrixDimension]){
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

int main(){
	int i, j, adjacencyMatrix[adjacencyMatrixDimension][adjacencyMatrixDimension];

	cout << "Enter the value of N\n";
	cin >> N;
	
	cout << "Enter the value of adjacency matrix\n";
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
	return 0;
}
