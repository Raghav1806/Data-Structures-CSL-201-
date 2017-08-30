// program to print the middle element (odd) and second middle (even) element of a linked list
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

void printMiddle(struct Node *head){
	struct Node *slow = head;
	struct Node *fast = head;

	while(fast != NULL && fast->next != NULL){
		fast = (fast->next)->next;
		slow = slow->next;
	}

	cout<<slow->data<<"\n";
}

int main(){
	head = NULL;
	int N, i, num;
	cout<<"Enter the number of elements in linked list:\n";
	cin>>N;
	cout<<"Enter the number of elements of linked list:\n";
	for(i = 0; i < N; i++){
		cin>>num;
		insertNode(num);
	}

	cout<<"The inserted linked list is:\n";
	display(head);

	cout<<"The middle element of linked list is:\n";
	printMiddle(head);
return 0;
}
