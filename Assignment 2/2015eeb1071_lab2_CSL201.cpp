/*

CSL 201 Lab Assignment #2
----------------------------------
----------------------------------
Question: Write a program (C / C++) to apply the concepts of stacks and queues for addressing 5 different types of queries.
----------------------------------
----------------------------------
These 5 queries are denoted by S, Q, I, E, and P and these query type identifiers correspond
to -

S: Performing Stack operations,
Q: Performing Queue operations,
I: Converting Infix expression to equivalent postfix expression,
E: Evaluating infix expression value and
P: Computing stack Permutation, respectively.
----------------------------------
----------------------------------
The first line of the input contains an integer T denoting the number of queries. Then there follows T lines, each line correspond to a query and query type is identified with the first character in that line which could be either S, Q, I, E, or P.
Query type identifier is then followed by parameters specific to that query. These parameters would be single-space separated.
---------------------------------
---------------------------------
Developed by: 
Raghav Sharma
2015EEB1071
---------------------------------
---------------------------------
Submitted on:
27th September, 2017

*/


#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
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

// stack operations
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

int checkIfValid_Stack(string A){
	int check1 = 0;
	int check2 = 0;
	int i, limit;
	
	limit = 0;
	
	for(i = 0; A[i] != '\0'; i++){
		if(A[i] == '#'){
			check1 = 1;
			break;
		}
	}
	
	limit = i;
	
	for(i = 1; i < limit; i++){
		if('0' <= A[i] && A[i] <= '9' || A[i] == 'P' || A[i] == 'F' || A[i] == 'E' || A[i] == 'N' || A[i] == ' ' || A[i] == '-')
			check2 = 1;
		else{
			check2 = 0;
			break;
		}	 
	}
	
	return check1*check2;
}



// queue operations
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

int checkIfValid_Queue(string A){
	int check1 = 0;
	int check2 = 0;
	int i, limit;
	
	limit = 0;
	
	for(i = 0; A[i] != '\0'; i++){
		if(A[i] == '#'){
			check1 = 1;
			break;
		}
	}
	
	limit = i;
	
	for(i = 1; i < limit; i++){
		if('0' <= A[i] && A[i] <= '9' || A[i] == 'D' || A[i] == 'F' || A[i] == 'E' || A[i] == 'N' || A[i] == ' ' || A[i] == '-')
			check2 = 1;
		else{
			check2 = 0;
			break;
		}	 
	}
	
	return check1*check2;
}

// functions for both stack and queue
int totalNumberOfElements(struct Node *head){
	int ans = 0;
	while(head != NULL){
		head = head->next;
		ans++;
	}
	
	return ans;
}

void display(struct Node *head){
	while(head != NULL){
		cout << head->data << " ";
		head = head->next;
	}
	
	cout << "\n";
}

// functions for infix to postfix conversion

// function to return precedence order of various operators
int precedence(char ch){

// 'a' refers to '<<'
// 'b' refers to '>>'
// 'c' refers to '<='
// 'd' refers to '>='
// 'e' refers to '=='
// 'f' refers to '!='

	switch(ch){
		case '|':
			return 1;
			
		case '^':
			return 2;
			
		case '&':
			return 3;
			
		case 'e':
		case 'f':
			return 4;
			
		case '<':
		case 'c':
		case 'd':
		case '>':
			return 5;
			
		case 'a':
		case 'b':
			return 6;
			
		case '+':
		case '-':
			return 7;
			
		case '*':
		case '/':
		case '%':
			return 8;			
	}
	
		return -1;
}

int checkIfValid_Infix(string A){

	head = NULL;
	int check1, check2, i, j, limit, x, check3, multiplier, check4, numberOfOperators, numberOfOperands, num[4];
	char op;
	check1 = 0;
	check2 = 1;
	check3 = 1;
	check4 = 0;
	numberOfOperators = numberOfOperands = 0;
	multiplier = 1;
	
	for(i = 0; A[i] != '\0'; i++){
		if(A[i] == '#'){
			check1 = 1;
			break;
		}
	}
	
	limit = i;
	
	for(i = 0; i < limit; i++){
		int x = 1;
				
		if('0' <= A[i] && A[i] <= '9'){
			int index = 0;
			int number = 0;
		
			if(A[i-1] == '-')
				x = -1;
			else
				x = 1;
			
		
			while('0' <= A[i] && A[i] <= '9'){
				num[index] = A[i] - '0';
				index++;
				i++;
			}
		
			for(j = 0; j < index; j++)
				number += num[j]*pow(10, index - j - 1);
			
			number = number*x;
			push(number);
		}
		
		numberOfOperands = totalNumberOfElements(head);
	}
	
	for(i = 1; i < limit; i++){
		if(A[i] == '<' && A[i+1] == '<'){
			if(multiplier != -1){
				check3 = 0;
				break;
			}
			multiplier *= -1;
			op = 'a';
			numberOfOperators++;
			i++;
		}
		
		else if(A[i] == '>' && A[i+1] == '>'){
			if(multiplier != -1){
				check3 = 0;
				break;
			}
			multiplier *= -1;
			op = 'b';
			numberOfOperators++;
			i++;
		}
		
		else if(A[i] == '<' && A[i+1] == '='){
			if(multiplier != -1){
				check3 = 0;
				break;
			}
			multiplier *= -1;
			op = 'c';
			numberOfOperators++;
			i++;
		}
		
		else if(A[i] == '>' && A[i+1] == '='){
			if(multiplier != -1){
				check3 = 0;
				break;
			}
			multiplier *= -1;
			op = 'd';
			numberOfOperators++;
			i++;
		}
		
		else if(A[i] == '=' && A[i+1] == '='){
			if(multiplier != -1){
				check3 = 0;
				break;
			}
			multiplier *= -1;
			op = 'e';
			numberOfOperators++;
			i++;
		}
		
		else if(A[i] == '!' && A[i] == '='){
			if(multiplier != -1){
				check3 = 0;
				break;
			}
			multiplier *= -1;
			op = 'f';
			numberOfOperators++;
			i++;
		}
		
		else if(A[i] == ' ')
			continue;
			
		else if('0' <= A[i] && A[i] <= '9'){
			if(multiplier != 1){
				check3 = 0;
				break;
			}
			else{
				multiplier *= -1;
				while('0' <= A[i] && A[i] <= '9')
					i++;
				i--;	
				continue;
			}
		}	
		
		else{
			op = A[i];
			numberOfOperators++;
			if(multiplier != -1){
				check3 = 0;
				break;
			}
			else
				multiplier *= -1;
		}
			
		if(precedence(op) == -1){
			check2 = 0;
			break;
		}	
	}
	
	if(numberOfOperands - 1 == numberOfOperators)
		check4 = 1;	
	
	return check1*check2*check3*check4;
}

// function for infix evaluation
int peek(struct Node *head){
	if(head != NULL)
		return head->data;
}

// functions for finding stack permutations

int isEmpty(struct Node *head){
	return(head == NULL);
}

void swap(int permutation[], int x, int y){
	int temp;
	temp = permutation[x];
	permutation[x] = permutation[y];
	permutation[y] = temp;
}

int findCeil(int permutation[], int x, int l, int h){
	int ceilIndex = l;
	int i;
	
	for(i = l+1; i <= h; i++){
		if(permutation[i] > x && permutation[i] < permutation[ceilIndex])
			ceilIndex = i;
	}
	
	return ceilIndex;
}

void reverse(int permutation[], int l, int h){
	while(l < h){
		swap(permutation, l, h);
		l++;
		h--;
	}
}

// returns 1 if given stack permutation is possible
int checkIfStackPermutation(int permutation[], int size){

	head = NULL;
	
	int buffer[size], i, beg1, beg2, num, topElement;
	for(i = 0; i < size; i++)
		buffer[i] = i + 1;
	
	// beg1 is associated with buffer[], original array
	// beg2 is associated with permutation[], array to be checked
	beg1 = 0;
	beg2 = 0;
	
	while(beg1 < size){
		num = buffer[beg1];
		beg1++;
		if(num == permutation[beg2]){
			beg2++;
			while(!isEmpty(head)){
				topElement = peek(head);
				if(topElement == permutation[beg2]){
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
	
	if(isEmpty(head) && beg2 == size)
		return 1;
	else
		return 0;		
}

void sortedPermutations(int permutation[], int size, int k){
	int i, check, count, buffer[size];
	count = 0;
	
	// print permutations one by one
	bool isFinished = false;
	
	while(!isFinished){	
		
		check = checkIfStackPermutation(permutation, size);
		
		if(check == 1){
		
			count++;
			if(count  == k){
				for(i = 0; i < size; i++)
					buffer[i] = permutation[i];
			}
		}
		
		// find the rightmost character which is smaller than its character
		for(i = size - 2; i >= 0; i--){
			if(permutation[i] < permutation[i+1])
				break;
		}
		
		// if there is no such integer, all are sorted in decreasing order
		if(i == -1)
			isFinished = true;
			
		else{
			// find the ceil of 'first integer'
			// it is the smallest integer greater than it
			int ceilIndex = findCeil(permutation, permutation[i], i+1, size-1);
			
			// swap first and second integers
			swap(permutation, i, ceilIndex);
			
			// reverse the subarray on right of 'first integer'
			reverse(permutation, i+1, size-1);
		}		
	}
	
	if(count >= k){
	
		cout << count++ << " ";
		
		for(i = 0; i < size; i++)
			cout << buffer[i] << " ";
		cout << "\n";
	}
	
	else{
		cout << "Error\n";
	}
}

int main(){

	int T;
	cin >> T;
	
	while(T--){
		string A;
		
		// to remove buffer in getline function
		cin >> ws;
		getline(cin, A);
		
		// stack operations
		if(A[0] == 'S'){
			int i, j, x, num[4], index, number, check;
			head = NULL;
			
			check = checkIfValid_Stack(A);
			
			if(check == 1){
				for(i = 1; A[i] != '#'; i++){
					x = 1;
				
					if('0' <= A[i] && A[i] <= '9'){
						index = 0;
						number = 0;
					
						if(A[i-1] == '-')
							x = -1;
						else
							x = 1;
						
					
						while('0' <= A[i] && A[i] <= '9'){
							num[index] = A[i] - '0';
							index++;
							i++;
						}
					
						for(j = 0; j < index; j++)
							number += num[j]*pow(10, index - j - 1);
						
						number = number*x;
						push(number);
					}
				
					if(A[i] == 'P')
						pop();		
				}
			
					cout << totalNumberOfElements(head) << " ";
					display(head);
			}
			
			else
				cout << "Error\n";		
		}// end of stack implementation
		
		else if(A[0] == 'Q'){
			int i, j, index, number, check, x, num[4];
			
			head = NULL;
			end = NULL;
			
			check = checkIfValid_Queue(A);
			
			if(check == 1){
				for(i = 1; A[i] != '\0'; i++){
					if('0' <= A[i] && A[i] <= '9'){
						index = 0;
						number = 0;
						
						if(A[i-1] == '-')
							x = -1;
						else
							x = 1;
						while('0' <= A[i] && A[i] <= '9'){
						num[index] = A[i] - '0';
						index++;
						i++;
							
						}
						
						for(j = 0; j < index; j++)
							number += num[j]*pow(10, index - j - 1);
						
						number = number*x;
						enqueue(number);		
					}
					
					if(A[i] == 'D')
						dequeue();
				}
				
				cout << totalNumberOfElements(head) << " ";
				display(head);
			}
			
			else{
				cout << "Error\n";
			}
			
		}// end of queue implementation
		
		else if(A[0] == 'I'){
			int check, x, top, i, index, j, number, num[4];
			char stackOperators[25], op, ch;
			top = -1;
			
			check = checkIfValid_Infix(A);
			
			if(check == 1){
				for(i = 1; A[i] != '#'; i++){
					if('0' <= A[i] && A[i] <= '9'){
						index = 0;
						number = 0;
						
						if(A[i-1] == '-')
							x = -1;
						else
							x = 1;
							
						while('0' <= A[i] && A[i] <= '9'){
							num[index] = A[i] - '0';
							index++;
							i++;
						}
						
						for(j = 0; j < index; j++)
							number += num[j]*pow(10, index - j - 1);
							
							i--;
							number = number*x;
							cout << number << " "; 		
					}
					
					else{
						if(top >= 0)
							ch = stackOperators[top];
							
						else
							ch = 'x';
						
						if(A[i] == '<' && A[i+1] == '<'){
							op = 'a';
							i++;
						}
						
						else if(A[i] == '>' && A[i+1] == '>'){
							op = 'b';
							i++;
						}
						
						else if(A[i] == '<' && A[i+1] == '='){
							op = 'c';
							i++;
						}
						
						else if(A[i] == '>' && A[i+1] == '='){
							op = 'd';
							i++;
						}
						
						else if(A[i] == '=' && A[i+1] == '='){
							op = 'e';
							i++;
						}
						
						else if(A[i] == '!' && A[i] == '='){
							op = 'f';
							i++;
						}
						
						else if(A[i] == ' ')
							continue;
						else
							op = A[i];
							
							
						if(top == -1 || precedence(op) >= precedence(ch)){
							top++;
							stackOperators[top] = op;
						}
						
						else{
							while(precedence(op) < precedence(ch) && top >= 0){
								if(ch == 'a'){
									cout << "<<" << " ";
									top--;
								}
								
								else if(ch == 'b'){
									cout << ">>" << " ";
									top--;
								}	
							
								else if(ch == 'c'){
									cout << "<=" << " ";
									top--;
								}
							
								else if(ch == 'd'){
									cout << ">=" << " ";
									top--;
								}
							
								else if(ch == 'e'){
									cout << "==" << " ";
									top--;
								}
							
								else if(ch == 'f'){
									cout << "!=" << " ";
									top--;
								}
							
								else{
									cout << ch << " ";
									top--;
								}
							
								if(top >= 0)
									ch = stackOperators[top];
								else
									ch = 'x';	
							}
							
							top++;
							stackOperators[top] = op;
						}				
					}
				}
				
				while(top >= 0){
			
					ch = stackOperators[top];
				
					if(ch == 'a'){
						cout << "<<" << " ";
						top--;
					}
							
					else if(ch == 'b'){
						cout << ">>" << " ";
						top--;
					}	
							
					else if(ch == 'c'){
						cout << "<=" << " ";
						top--;
					}
							
					else if(ch == 'd'){
						cout << ">=" << " ";
						top--;
					}
							
					else if(ch == 'e'){
						cout << "==" << " ";
						top--;
					}
							
					else if(ch == 'f'){
						cout << "!=" << " ";
						top--;
					}	
					
					else{
						cout << ch << " ";
						top--;
					}
				}
				
				cout << "\n";
			}
			
			else if(check == 0){
				cout << "Error\n";
			}
		}// end of infix to postfix
		
		else if(A[0] == 'E'){
			head = NULL;
			
			int check, x, top, i, index, j, number, num[4], operand1, operand2;
			char stackOperators[25], op, ch;
			top = -1;
			
			check = checkIfValid_Infix(A);
			
			if(check == 1){
				for(i = 1; A[i] != '#'; i++){
					if('0' <= A[i] && A[i] <= '9'){
						index = 0;
						number = 0;
						
						if(A[i-1] == '-')
							x = -1;
						else
							x = 1;
							
						while('0' <= A[i] && A[i] <= '9'){
							num[index] = A[i] - '0';
							index++;
							i++;
						}
						
						for(j = 0; j < index; j++)
							number += num[j]*pow(10, index - j - 1);
							
							i--;
							number = number*x;
							push(number); 
					}
					
					else{
						if(top >= 0)
							ch = stackOperators[top];
							
						else
							ch = 'x';
						
						if(A[i] == '<' && A[i+1] == '<'){
							op = 'a';
							i++;
						}
						
						else if(A[i] == '>' && A[i+1] == '>'){
							op = 'b';
							i++;
						}
						
						else if(A[i] == '<' && A[i+1] == '='){
							op = 'c';
							i++;
						}
						
						else if(A[i] == '>' && A[i+1] == '='){
							op = 'd';
							i++;
						}
						
						else if(A[i] == '=' && A[i+1] == '='){
							op = 'e';
							i++;
						}
						
						else if(A[i] == '!' && A[i] == '='){
							op = 'f';
							i++;
						}
						
						else if(A[i] == ' ')
							continue;
						else
							op = A[i];
							
							
						if(top == -1 || precedence(op) >= precedence(ch)){
							top++;
							stackOperators[top] = op;
						}
						
						else{
							while(precedence(op) < precedence(ch) && top >= 0){
							
								if(ch == 'a'){
									top--;
									operand2 = peek(head);
									pop();
									operand1 = peek(head);
									pop();
									operand1 = operand1 << operand2;
									push(operand1);
								}
								
								else if(ch == 'b'){
									top--;
									operand2 = peek(head);
									pop();
									operand1 = peek(head);
									pop();
									operand1 = operand1 >> operand2;
									push(operand1);
								}	
							
								else if(ch == 'c'){
									top--;
									operand2 = peek(head);
									pop();
									operand1 = peek(head);
									pop();
									operand1 = operand1 <= operand2;
									push(operand1);
								}
							
								else if(ch == 'd'){
									top--;
									operand2 = peek(head);
									pop();
									operand1 = peek(head);
									pop();
									operand1 = operand1 >= operand2;
									push(operand1);
								}
							
								else if(ch == 'e'){
									top--;
									operand2 = peek(head);
									pop();
									operand1 = peek(head);
									pop();
									operand1 = operand1 == operand2;
									push(operand1);
								}
							
								else if(ch == 'f'){
									top--;
									operand2 = peek(head);
									pop();
									operand1 = peek(head);
									pop();
									operand1 = operand1 != operand2;
									push(operand1);
								}
							
								else if(ch == '+'){
									top--;
									operand2 = peek(head);
									pop();
									operand1 = peek(head);
									pop();
									operand1 = operand1 + operand2;
									push(operand1);
								}
								
								else if(ch == '-'){
									top--;
									operand2 = peek(head);
									pop();
									operand1 = peek(head);
									pop();
									operand1 = operand1 - operand2;
									push(operand1);
								}
								
								else if(ch == '/'){
									top--;
									operand2 = peek(head);
									pop();
									operand1 = peek(head);
									pop();
									operand1 = operand1 / operand2;
									push(operand1);
								}
								
								else if(ch == '%'){
									top--;
									operand2 = peek(head);
									pop();
									operand1 = peek(head);
									pop();
									operand1 = operand1 % operand2;
									push(operand1);
								}
								
								else if(ch == '&'){
									top--;
									operand2 = peek(head);
									pop();
									operand1 = peek(head);
									pop();
									operand1 = operand1 & operand2;
									push(operand1);
								}
								
								else if(ch == '^'){
									top--;
									operand2 = peek(head);
									pop();
									operand1 = peek(head);
									pop();
									operand1 = operand1 ^ operand2;
									push(operand1);
								}
								
								else if(ch == '|'){
									top--;
									operand2 = peek(head);
									pop();
									operand1 = peek(head);
									pop();
									operand1 = operand1 | operand2;
									push(operand1);
								}
								
								else if(ch == '>'){
									top--;
									operand2 = peek(head);
									pop();
									operand1 = peek(head);
									pop();
									operand1 = operand1 > operand2;
									push(operand1);
								}
								
								else if(ch == '<'){
									top--;
									operand2 = peek(head);
									pop();
									operand1 = peek(head);
									pop();
									operand1 = operand1 < operand2;
									push(operand1);
								}
								
								else if(ch == '*'){
									top--;
									operand2 = peek(head);
									pop();
									operand1 = peek(head);
									pop();
									operand1 = operand1 * operand2;
									push(operand1);
								}
																
								
								if(top >= 0)
									ch = stackOperators[top];
								else
									ch = 'x';	
							}
							
							top++;
							stackOperators[top] = op;
						}				
					}
				}
				
				while(top >= 0){
				
					ch = stackOperators[top];
					if(ch == 'a'){
						top--;
						operand2 = peek(head);
						pop();
						operand1 = peek(head);
						pop();
						operand1 = operand1 << operand2;
						push(operand1);
					}
					
					else if(ch == 'b'){
						top--;
						operand2 = peek(head);
						pop();
						operand1 = peek(head);
						pop();
						operand1 = operand1 >> operand2;
						push(operand1);
					}	
				
					else if(ch == 'c'){
						top--;
						operand2 = peek(head);
						pop();
						operand1 = peek(head);
						pop();
						operand1 = operand1 <= operand2;
						push(operand1);
					}
				
					else if(ch == 'd'){
						top--;
						operand2 = peek(head);
						pop();
						operand1 = peek(head);
						pop();
						operand1 = operand1 >= operand2;
						push(operand1);
					}
				
					else if(ch == 'e'){
						top--;
						operand2 = peek(head);
						pop();
						operand1 = peek(head);
						pop();
						operand1 = operand1 == operand2;
						push(operand1);
					}
				
					else if(ch == 'f'){
						top--;
						operand2 = peek(head);
						pop();
						operand1 = peek(head);
						pop();
						operand1 = operand1 != operand2;
						push(operand1);
					}
				
					else if(ch == '+'){
						top--;
						operand2 = peek(head);
						pop();
						operand1 = peek(head);
						pop();
						operand1 = operand1 + operand2;
						push(operand1);
					}
					
					else if(ch == '-'){
						top--;
						operand2 = peek(head);
						pop();
						operand1 = peek(head);
						pop();
						operand1 = operand1 - operand2;
						push(operand1);
					}
					
					else if(ch == '/'){
						top--;
						operand2 = peek(head);
						pop();
						operand1 = peek(head);
						pop();
						operand1 = operand1 / operand2;
						push(operand1);
					}
					
					else if(ch == '%'){
						top--;
						operand2 = peek(head);
						pop();
						operand1 = peek(head);
						pop();
						operand1 = operand1 % operand2;
						push(operand1);
					}
					
					else if(ch == '&'){
						top--;
						operand2 = peek(head);
						pop();
						operand1 = peek(head);
						pop();
						operand1 = operand1 & operand2;
						push(operand1);
					}
					
					else if(ch == '^'){
						top--;
						operand2 = peek(head);
						pop();
						operand1 = peek(head);
						pop();
						operand1 = operand1 ^ operand2;
						push(operand1);
					}
					
					else if(ch == '|'){
						top--;
						operand2 = peek(head);
						pop();
						operand1 = peek(head);
						pop();
						operand1 = operand1 | operand2;
						push(operand1);
					}
					
					else if(ch == '>'){
						top--;
						operand2 = peek(head);
						pop();
						operand1 = peek(head);
						pop();
						operand1 = operand1 > operand2;
						push(operand1);
					}
					
					else if(ch == '<'){
						top--;
						operand2 = peek(head);
						pop();
						operand1 = peek(head);
						pop();
						operand1 = operand1 < operand2;
						push(operand1);
					}
					
					else if(ch == '*'){
						top--;
						operand2 = peek(head);
						pop();
						operand1 = peek(head);
						pop();
						operand1 = operand1 * operand2;
						push(operand1);
					}
					
				}
				
				cout << peek(head) << "\n";
				pop();
			}
			
			else{
				cout << "Error\n";
			}
			
		}// end of evaluate infix
		
		else if(A[0] == 'P'){
		
			head = NULL;
			int i, num[15], index, j, serial;
			long long int number, size, k;
			serial = -1;
			
			for(i = 1; A[i] != '\0'; i++){
				if(A[i] == ' ')
					continue;
				if('0' <= A[i] && A[i] <= '9'){
					index = 0;
					number = 0;
					serial ++;
					
					while('0' <= A[i] && A[i] <= '9'){
						num[index] = A[i] - '0';
						index++;
						i++;
					}
					
					for(j = 0; j < index; j++)
						number += num[j]*pow(10, index - j - 1);
						
					i--;	
					
					if(serial == 0)
						size = number;
					else if(serial == 1)
						k = number;	
				}	
			}
			
			int permutation[size];
			
			for(i = 0; i < size; i++)
				permutation[i] = i + 1;
				
			sortedPermutations(permutation, size, k);	
		}// end of stack permutations
		
		else{
			cout << "Error\n";
		}
		
	}// end of while loop
	
	return 0;
}

