// program to reverse a linked list

#include <iostream>
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
		cout<<head->data<<"->";
		head = head->next;
	}

	cout<<"\n";
}

void insertNode(int x){
	struct Node *newptr = createNewNode(x);
	if(head == NULL)
		head = newptr;
	else{
		struct Node *temp = head;
		head = newptr;
		newptr->next = temp;
	}
		
}

void reverse(){
	struct Node *curr, *prev, *temp;
	curr = head;
	prev = NULL;

	while(curr != NULL){
		temp = curr->next;
		curr->next = prev;
		prev = curr;
		curr = temp;
	}

	head = prev;
}

int main(){
	int N, i, x;
	head = NULL;
	cout<<"Enter the number of nodes in linked list: ";
	cin>>N;
		
	cout<<"Enter the numbers:\n";
	for(i = 0; i < N; i++){
		cin>>x;
		insertNode(x);
	}

	cout<<"The elements of linked list are:\n";
	display(head);

	cout<<"The elements after reversing the linked list are:\n";
	reverse();
	display(head);

return 0;
}
