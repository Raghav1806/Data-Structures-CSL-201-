// program to evaluate infix expression using two stacks

#include <iostream>
#include <cstdlib>
using namespace std;

// stack node for operator
struct Node{
	char data;
	struct Node *next;
}*head;

// stack for operand
float A[100];
int index = -1;

// function returns new node of stack
struct Node *createNewNode(char x){
	struct Node *newptr = new Node;
	newptr->data = x;
	newptr->next = NULL;
	
	return newptr;
}

// function inserts new node in stack
void push(char x){
	struct Node *newptr = createNewNode(x);
	newptr->next = head;
	head = newptr;
}

// function deletes a node from stack
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

// returns top most element of stack
char top(){
	if(head != NULL)
		return head->data;
	else
		return '!';
}

int findPower(int y){
	int i, ans;
	ans = 1;
	for(i = 0; i < y; i++)
		ans *= 10;
	
	return ans;
}

int evaluateNumber(int X[], int up){
	int i, ans;
	ans = 0;
	for(i = 0; i < up; i++){
		ans += X[i]*findPower(up - i - 1);
	}
	
	return ans;
}

float evaluate(float x, float y, char ch){
	if(ch == '+')
		return x+y;
	if(ch == '-')
		return x-y;
	if(ch == '*')
		return x*y;
	if(ch == '/')
		return x/y;		
}

int evaluateInfix(char exp[]){
	int i, ans, up, number;
	float x, operand1, operand2;
	int k;
	ans = 0;
	int X[10];
	char ch;
	
	i = 0;
	
	while(exp[i] != '\0'){
		up = 0;
		
		//cout << "index = " << index << "\n";
		
		while('0' <= exp[i] && exp[i] <= '9'){
			X[up] = exp[i] - '0';
			up++;
			i++;
		}
		
		if(up > 0){
			number = evaluateNumber(X, up);
			// adding the number to stack
			index++;
			A[index] = number;
		}
		
		else{
			ch = top();
			
			if(isEmpty() || precedence(exp[i]) >= precedence(ch) || exp[i] == '(')
				push(exp[i]);
			
				
			else if(exp[i] == ')'){
				while(ch != '('){
					operand1 = A[index];
					index--;
					operand2 = A[index];
					index--;
					x = evaluate(operand2, operand1, ch);
					index++;
					A[index] = x;
					pop();
					ch = top();
				}
				
				// popping '('
				pop();
			}
			
			else{
				while(precedence(exp[i]) < precedence(ch)){
					operand1 = A[index];
					index--;
					operand2 = A[index];
					index--;
					x = evaluate(operand2, operand1, ch);
					index++;
					A[index] = x;
					pop();
					ch = top();
					
				}
				
				push(exp[i]);
			}
			
			i++;
		}
		
	}
	
	while(!isEmpty()){
		operand1 = A[index];
		index--;
		operand2 = A[index];
		index--;
		ch = top();
		pop();
		
		x = evaluate(operand2, operand1, ch);
		index++;
		A[index] = x;
	}
	
	cout << A[0] << "\n";
} 

int main(){
	head = NULL;
	char exp[250];
	
	cout << "Enter the infix expression\n";
	cin >> exp;
	
	evaluateInfix(exp);
	
	return 0;
}
