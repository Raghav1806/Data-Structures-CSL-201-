#include <iostream>
#include <cstdlib>
using namespace std;

struct Node{
	int data;
	struct Node *next;
}*head;

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

void push(int x){
	struct Node *newptr = createNewNode(x);
	newptr->next = head;
	head = newptr;
}

void pop(){
	struct Node *temp = head;
	head = head->next;
	free(temp);
}

int main(){
	head = NULL;
	push(1);
	push(2);
	push(3);
	push(4);
	push(5);
	display(head);
	pop();
	display(head);
	pop();
	display(head);

	return 0;
}
