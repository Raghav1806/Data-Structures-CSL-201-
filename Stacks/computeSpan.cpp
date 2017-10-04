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
		cout << head->data << " ";
		head = head->next;
	}
	
	cout << "\n";
}

void push(int x){
	struct Node *newptr = createNewNode(x);
	
	if(head == NULL){
		head = newptr;
		return;
	}
	
	else{
		newptr->next = head;
		head = newptr;
	}
}

void pop(){
	if(head != NULL){
		struct Node *temp = head;
		head = head->next;
		temp->next = NULL;
		free(temp);
	}	
}

int isEmpty(){
	return(head == NULL);
}

int top(){
	if(head != NULL)
		return head->data;
}

int main(){
	head = NULL;
	int size, i, price;
	cout << "Enter the number of days\n";
	cin >> size;
	cout << "Enter the stock prizes for each day\n";
	
	int span[size], stockPrice[size];
	for(i = 0; i < size; i++)
		span[i] = 1;
	
	for(i = 0; i < size; i++)
		cin >> stockPrice[i];
		
	for(i = 0; i < size; i++){
		while(!isEmpty() && stockPrice[top()] <= stockPrice[i])
			pop();

		if(isEmpty())
			span[i] = i;
		else
			span[i] = i - top();
		push(i);	
	}	
	
	cout << "The span is:\n";
	span[0] = 1;
	for(i = 0; i < size; i++)
		cout << span[i] << " ";
	cout << "\n";	
			
	return 0;
}
