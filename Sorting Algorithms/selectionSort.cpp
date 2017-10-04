#include <iostream>
using namespace std;

int main(){
	int size, i, j, min, temp, minIndex;
	cout << "Enter the size of array\n";
	cin >> size;
	int A[size];
	
	cout << "Enter the elements of array\n";
	for(i = 0; i < size; i++)
		cin >> A[i];
		
	for(i = 0; i < size; i++){
		min = A[i];
		minIndex = i;
		for(j = i + 1; j < size; j++){
			 if(min > A[j]){
			 	min = A[j];
			 	minIndex = j;
			 }
		}
		
		temp = A[i];
		A[i] = A[minIndex];
		A[minIndex] = temp; 
	}	
	
	cout << "The sorted array is\n";
	for(i = 0; i < size; i++)
		cout << A[i] << " ";
	cout << "\n";	
	return 0;
}
