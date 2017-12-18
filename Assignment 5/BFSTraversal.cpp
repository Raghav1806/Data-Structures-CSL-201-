// program for demonstrating BFS traversal in an adjacency matrix
#include <iostream>
#include <cstdlib>
using namespace std;
#define INF 999999
// allocated space for adjacency matrix representation
#define adjacencyMatrixDimension 150

// N -> number of vertices in graph
int N;

struct queueNode{
	int data;
	struct queueNode *next;
}*queueHead, *queueTail;

struct queueNode *createNewNode(int x){
	struct queueNode *newptr = new queueNode;
	newptr->data = x;
	newptr->next = NULL;

	return newptr;
}

void insertQueueNode(int x){
	struct queueNode *newptr = createNewNode(x);
	if(queueHead == NULL){
		queueHead = queueTail = newptr;
	}
	else{
		queueTail->next = newptr;
		queueTail = newptr;
	}
}

int queueFront(){
	return queueHead->data;
}

bool queueIsEmpty(){
	if(queueHead == NULL){
		return true;
	}
	else{
		return false;
	}
}

void deleteFromQueue(){
	struct queueNode *temp = queueHead;
	queueHead = queueHead->next;
	free(temp);
}

int checkIfBFSIsCompleted(bool visited[N]){
	int i;
	for(i = 0; i < N; i++){
		if(!visited[i]){
			return i;
		}
	}
	return -1;
}


void BFS(int adjacencyMatrix[adjacencyMatrixDimension][adjacencyMatrixDimension], bool visited[N], int S, int D){
	int i, x, numberOfNodes;

	// stores the number of nodes in a particular level
	numberOfNodes = 0;

	// checks whether all nodes have been covered in primary BFS traversal
	int check;

	// source vertex is visited (by default)
	visited[S] = true;
	insertQueueNode(S);

	while(!queueIsEmpty()){
		x = queueFront();
		deleteFromQueue();

		// get all the adjacent vertices of the dequeued vertex s
		for(i = 0; i < N; i++){
			numberOfNodes = 0;
			if(adjacencyMatrix[x][i] == 1 && !visited[i]){
				visited[i] = true;
				insertQueueNode(i);
				numberOfNodes++;
			}
		}
		cout << numberOfNodes << " ";
	}

	// check is the index of new source vertex
	check = checkIfBFSIsCompleted(visited);
	if(check != -1){
		BFS(adjacencyMatrix, visited, check, D);
	}

	cout << "0\n";

}

int main(){
	int D, S, i, j;

	// D -> whether graph is directed or not
	// S -> source vertex (1 indexed)
	cout << "Enter the value of N, D, and S\n";
	cin >> N >> D >> S;

	// 1 based indexing is used in input
	S--;
	
	int adjacencyMatrix[adjacencyMatrixDimension][adjacencyMatrixDimension];
	bool visited[N];

	for(i = 0; i < N; i++){
		visited[i] = false;
	}
	
	cout << "Enter the value of adjacency matrix\n";
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			cin >> adjacencyMatrix[i][j];
		}
	}
	
	BFS(adjacencyMatrix, visited, S, D);

	return 0;
}