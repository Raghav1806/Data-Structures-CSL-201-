// program for infix to postfix conversion

#include <iostream>
#include <cstdlib>
using namespace std;

// basic structure of a node in stack of operators
struct Node{
	char data;
	struct Node *next;
}*head;

// returns pointer to new node
struct Node *createNewNode(char x){
	struct Node *newptr = new Node;
	newptr->data = x;
	newptr->next = NULL;
	
	return newptr;
}

// inserts an element to stack
void push(char x){
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

// deletes an element from stack
void pop(){
	struct Node *temp = head;
	head = head->next;
	free(temp);
}

// returns the element at top of stack
char top(){
	if(head != NULL)
		return head->data;
	else
		return '!';
}

// function to return precedence order of various operators
int precedence(char ch){
	switch(ch){
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
			
		case '^':
			return 3;
	}
	
		return -1;
}

// returns 1 if stack is empty
int isEmpty(){
	return(head == NULL);
}

// returns 1 if operand is present
int isOperand(char x){
	return (x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z');
}

void infixToPostfix(char exp[]){
	int i;
	char ch;
	for(i = 0; exp[i] != '\0'; i++){
		// displays the current situation of stack
		if(isOperand(exp[i])){
			cout << exp[i] << " ";
		}
		
		else{
				ch = top();
				
			if(isEmpty() || precedence(exp[i]) >= precedence(ch) || exp[i] == '(')
				push(exp[i]);
				
			else if(exp[i] == ')'){
				while(ch != '('){
					cout << ch << " ";
					pop();
					ch = top();
				}
				
				// popping '('
				pop();		
			}
				
			else{
				while(precedence(exp[i]) < precedence(ch)){
					cout << ch << " ";
					pop();
					ch = top();
				}
				
				push(exp[i]);
			}
		}
	}
	
	while(!isEmpty()){
		ch = top();
		pop();
		cout << ch << " ";
	}
	
	cout << "\n";
}

int main(){
	// head corresponds to stack of operators
	head = NULL;
	
	char exp[250];
	cout << "Enter the infix expression\n";
	cin >> exp;
	
	infixToPostfix(exp);
	
	return 0;
}
