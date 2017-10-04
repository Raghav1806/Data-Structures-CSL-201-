#include <iostream>
#include <algorithm>
using namespace std;

int binarySearch(int A[], int size, int num){
	int low, high, mid, check;
	check = 0;

	low = 0;
	high = size-1;
	mid = (low + high)/2;
	
	while(low < high){
	
		mid = (low + high)/2;
		
		if(A[mid] > num){
			high = mid;
		}
		
		else if(A[mid] < num){
			low = mid;
		}
		
		else if(A[mid] == num){
			check = 1;
			break;
		}
	}
	
	return check;
}

int main(){
	int size, i, num, check;

	cout << "Enter the size of array\n";
	cin >> size;
	int A[size];

	cout << "Enter the elements of array\n";
	for(i = 0; i < size; i++)
		cin >> A[i];
		
	sort(A, A + size);
	
	cout << "Enter the element to be searched for\n";
	cin >> num;
	
	check = binarySearch(A, size, num);
	
	if(check == 1)
		cout << "Found!\n";
	else
		cout << "Not found!\n";	
		
	return 0;	
}
