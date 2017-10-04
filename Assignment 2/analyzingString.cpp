// program to extract integers from a character array
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int main(){
	int i, index, x, num[4], number, j;
	number = 0;
	x = 1;
	index = 0;
	string A;

	cout << "Enter the characters\n";
	getline(cin, A);

	for(i = 0; A[i] != '\0'; i++)
		cout << A[i] << " ";
	cout << "\n";
	
	for(i = 0; A[i] != '\0'; i++){
		if('0' <= A[i] && A[i] <= '9'){
			if(A[i-1] == '-')
				x = -1;
			while('0' <= A[i] && A[i] <= '9'){
				num[index] = A[i] - '0';
				index++;
				i++;
			}	
			
			for(j = 0; j < index; j++)
				number += num[j]*pow(10, index - j - 1);
				
			number = number*x;	
		}
	}
	
	cout << number << " ";
	cout << number + 1 << "\n";
		
	return 0;
}
