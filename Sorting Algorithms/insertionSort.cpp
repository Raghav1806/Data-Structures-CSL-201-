// insertion sort algorithm 

#include <iostream>
using namespace std;

int main(){
	int size, i, j, curr;
	cout << "Enter the size of array to be sorted\n";
	cin >> size;
	
	int A[size];
	cout << "Enter the elements of array\n";

	for(i = 0; i < size; i++)
		cin >> A[i];
	
	for(i = 0; i < size - 1; i++){
		j = i + 1;
		curr = A[j];
		while(j > 0 && A[j - 1] > A[j]){
			A[j] = A[j - 1];
			A[j - 1] = curr;
			j--;
		}
	}
	
	cout << "The sorted array is\n";
	for(i = 0; i < size; i++)
		cout << A[i] << " ";
	cout << "\n";	
			
	return 0;
}
