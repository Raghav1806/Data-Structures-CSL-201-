#include <iostream>
#include <cstdlib>
using namespace std;

struct Node{
	int data;
	struct Node *next;
}*head, *end;

struct Node *createNewNode(int x){
	struct Node *newptr = new Node;
	newptr->data = x;
	newptr->next = NULL;
	
	return newptr;
}

void display(struct Node *head){
	while(head != NULL){
		cout << head->data << "->";
		head = head->next;
	}
	
	cout << "\n";
}

void enqueue(int x){
	struct Node *newptr = createNewNode(x);
	if(head == NULL && end == NULL){
		head = end = newptr;
		return;
	}
	
	else{
		end->next = newptr;
		end = newptr;
	}
}

void dequeue(){
	struct Node *temp = head;
	head = head->next;
	free(temp);
}

int main(){
	head = end = NULL;
	enqueue(1);
	enqueue(2);
	enqueue(3);
	enqueue(4);
	enqueue(5);
	display(head);
	dequeue();
	display(head);
	dequeue();
	display(head);

	return 0;
}
