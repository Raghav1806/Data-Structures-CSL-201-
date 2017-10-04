// Program to print all the possible permutations of a given array in lexicographical order
#include <iostream>
#include <algorithm>
using namespace std;

// function compares two integers
int compare(int a, int b){
	return (a-b);
}

// function swaps elements of A[] at indices x and y
void swap(int A[], int x, int y){
	int temp;
	temp = A[x];
	A[x] = A[y];
	A[y] = temp;
}

// function finds the index of smallest integer which is greater than 'x' and is present in A[l..h], and returns its index
int findCeil(int A[], int x, int l, int h){
	int ceilIndex = l;
	int i;
	
	// Iterate through rest of the elements and find the smallest character greater than 'x'
	for(i = l+1; i <= h; i++){
		if(A[i] > x && A[i] < A[ceilIndex])
			ceilIndex = i;
	}
	
	return ceilIndex;
}

// function to reverse the substring
void reverse(int A[], int l, int h){
	while(l < h){
		swap(A, l, h);
		l++;
		h--;
	}
}

void sortedPermutations(int A[], int size){
	int i;
	// sort the array in increasing order
	sort(A, A+size);
	
	// print permutations one by one
	bool isFinished = false;
	while(!isFinished){
		// print current permutation
		for(i = 0; i < size; i++)
			cout << A[i];
		cout << "\n";
		
		// find the rightmost character which is smaller than its character
		for(i = size-2; i >= 0; i--){
			if(A[i] < A[i+1])
				break;
		}
		
		// if there is no such integer, all are sorted in decreasing order
		if(i == -1)
			isFinished = true;
		else{
			// find the ceil of 'first integer' 
			// it is the smallest integer greater than it
			int ceilIndex = findCeil(A, A[i], i+1, size-1);
			// swap first and second integers
			swap(A, i, ceilIndex);
			
			// reverse the subarray on right of 'first integer'
			reverse(A, i+1, size-1);
		}
	}
}

int main(){
	int size, i;
	cout << "Enter the size of array\n";
	cin >> size;
	int A[size];
	cout << "Enter the elements of array\n";

	for(i = 0; i < size; i++)
		cin >> A[i];

	sortedPermutations(A, size);		

	return 0;
}


