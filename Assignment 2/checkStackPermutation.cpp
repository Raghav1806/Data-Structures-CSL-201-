// Program to check whether one sequence is possible stack permutation of other
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

void push(int x){
	struct Node *newptr = createNewNode(x);
	newptr->next = head;
	head = newptr;
}

void pop(){
	if(head != NULL){
		struct Node *temp = head;
		head = head->next;
		free(temp);
	}
}

// for debugging
void display(struct Node *head){
	while(head != NULL){
		cout << head->data << " ";
		head = head->next;
	}
	
	cout << "\n";
}

// returns 1 if stack is empty
int isEmpty(){
	return(head == NULL);
}

// returns topmost element of stack
int peek(){
	if(head != NULL)
		return head->data;
}

// returns 1 if given stack permutation is possible
int checkStackPermutation(int A[], int B[], int size){
	// beg1 is with A[], original array
	// beg2 is with B[], permutaion to be checked
	int beg1, beg2, num, topElement;

	beg1 = 0;
	beg2 = 0;
	
	while(beg1 < size){
		num = A[beg1];
		beg1++;
		if(num == B[beg2]){
			beg2++;
			while(!isEmpty()){
				topElement = peek();
				if(topElement == B[beg2]){
					pop();
					beg2++;
				}
				else
					break;
			}
		}
		else
			push(num);
	}
	
	if(isEmpty() && beg2 == size)
		return 1;
	else
		return 0;
}

int main(){
	head = NULL;
	int n, i, check;
	cout << "Enter the size of array\n";
	cin >> n;
	
	// A[n] stores original sequence
	// B[n] stores sequence to be checked
	int A[n], B[n];
	
	cout << "Enter the original array\n";
	for(i = 0; i < n; i++)
		cin >> A[i];
	
	cout << "Enter the sequence to be checked\n";
	for(i = 0; i < n; i++)
		cin >> B[i];
		
	check = checkStackPermutation(A, B, n);
	
	if(check == 1)
		cout << "Possible!\n";
	else
		cout << "Not Possible\n";
		
	return 0;
}
