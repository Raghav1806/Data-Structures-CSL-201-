// program to implement merge sort algorithm
#include <iostream>
using namespace std;

void merge(int A[], int beg, int mid, int end){
	int i, j, k;
	int n1 = mid - beg + 1;
	int n2 = end - mid;
	
	// temporary arrays
	int L[n1], R[n2];
	
	for(i = 0; i < n1; i++)
		L[i] = A[beg + i];
		
	for(j = 0; j < n2; j++)
		R[j] = A[mid + 1 + j];
		
	// merge the temporary arrays back into A[]
	i = 0;		// initial index of L[]
	j = 0;		// initial index of R[]
	k = beg;	// initial index of merged subarray 
	
	while(i < n1 && j < n2){
		if(L[i] <= R[j]){
			A[k] = L[i];
			i++;
			k++;
		}
		else{
			A[k] = R[j];
			j++;
			k++;
		}
	}	
	
	// copy the remaining elements (if any)
	while(i < n1){
		A[k] = L[i];
		i++;
		k++;
	}
	
	while(j < n2){
		A[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(int A[], int beg, int end){
	int mid;
	if(end > beg){
		mid = (beg + end)/2;
		mergeSort(A, beg, mid);
		mergeSort(A, mid+1, end);
		merge(A, beg, mid, end);
	}
}

int main(){
	int size, i, beg, end;
	cout << "Enter the size of array to be sorted\n";
	cin >> size;
	int A[size];
	
	beg = 0;
	end = size-1;
	
	cout << "Enter the elements of array\n";
	for(i = 0; i < size; i++)
		cin >> A[i];
		
	mergeSort(A, beg, end);
	
	cout << "The sorted array is\n";
	for(i = 0; i < size; i++)
		cout << A[i] << " ";
	cout << "\n";
	
	return 0;
}
