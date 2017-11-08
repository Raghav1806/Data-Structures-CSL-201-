#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int A[100];

int convertIntoArray(string S){
	int i, index, number, num[4], x, j, arrayIndex;
	arrayIndex = 0;
	for(i = 1; S[i] != '\0'; i++){
		if('0' <= S[i] && S[i] <= '9'){
			index = 0;
			number = 0;
			
			if(S[i-1] == '-')
				x = -1;
			else
				x = 1;
				
			while('0' <= S[i] && S[i] <= '9'){
				num[index] = S[i] - '0';
				index++;
				i++;
			}
			
			for(j = 0; j < index; j++)
				number += num[j]*pow(10, index - j - 1);
			number = number*x;
			A[arrayIndex] = number;
			arrayIndex++;			
		}
	}
	
	return arrayIndex;
}

int main(){

	string S;
	int i, size;
	
	// to remove buffer in getline function
	cin >> ws;
	getline(cin, S);
	size = convertIntoArray(S);
	
	cout << "The inserted array is\n";
	for(i = 0; i < size; i++)
		cout << A[i] << " ";
	cout << "\n";	
	return 0;
}
