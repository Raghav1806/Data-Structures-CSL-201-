/*
CSL 201: Assignment 1
-------------------------------------------------------------------------------
Q: Write a program in C or C++ for computing accurately the factorial of any given non-negative number.  You need to likely use linked lists concepts to perform this computation. 
-------------------------------------------------------------------------------
Developed by: Raghav Sharma, 2015eeb1071
Date of Submission: 26/08/2017
-------------------------------------------------------------------------------
*/

#include <iostream>
#include <fstream>
using namespace std;

// basic structure of a node in linked list 
struct Node{
	int data;
    	struct Node *next;
};
 
// function to reverse a linked list, so as to print it in the desired order
struct Node *reverse(struct Node *head){
   	struct Node *prev, *curr, *Next;
    	prev = NULL;
    	curr = head;
 
    	while(curr != NULL){
        	Next = curr -> next;
        	curr -> next = prev;
        	prev = curr;
        	curr = Next;
    	}

    	head = prev;
    	return head;
}

// function to print the linked list in usual order 
void print(struct Node *head){
     	while(head != NULL){
        	cout << head->data;
        	head = head->next;
    	}
	cout<<"\n";
}

// function to insert at the end of linked list 
struct Node *insert(struct Node *head, int val){
    	struct Node *temp = new Node;
    	struct Node *temp1 = head;
    	temp->data = val;
    	temp->next = NULL;

    		if(head == NULL){
        		head = temp;
        		return head;
    		}

    	temp1 = head;

    	while(temp1->next != NULL){
        	temp1 = temp1->next;
    	}

    	temp1-> next = temp;
    	return head;
}
 
// function finds factorial of a large number
void factorial(int n){

	int i, k, index, product, carry;
	k = 0;
	index = 1;
	carry = 0;

	struct Node *temp = NULL;
	struct Node *head = NULL;
 
    	temp = insert(temp, 1);
    	head = temp;

    	for(i = 2; i <= n; i++){
            	k = 0;
            	temp = head;
            	while(k < index){
                	product = (temp->data) * i + carry;
                	temp->data = product % 10;
                	carry = product/10;
                		if(carry > 0 && temp->next == NULL){
                    			index++;
                    			temp = insert(temp, 0);
                		}
                	k++;
                	temp = temp->next;
            	}
    	}
    
	print(reverse(head));
}
 
int main(void){

	int T, number;
	fstream inputFile("input.txt");
	fstream outputFile("out.txt");
	inputFile >> T;
	while(T--){
		inputFile >> number;
		factorial(number);
	}

    	return 0;
}
