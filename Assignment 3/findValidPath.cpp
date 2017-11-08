// program to print path from a node to a given node in a binary tree
#include <iostream>
#include <vector>
using namespace std;

struct Node{
	int data;
	struct Node *left;
	struct Node *right;
}*root;

struct Node *createNewNode(int x){
	struct Node *newptr = new Node;
	newptr->data = x;
	newptr->left = NULL;
	newptr->right = NULL;

	return newptr;
}

struct Node *findInBST(struct Node *root, int x){
	if(root == NULL)
		return NULL;
	if(root->data == x)
		return root;
	if(root->data > x)
		findInBST(root->left, x);
	else
		findInBST(root->right, x);
}

bool hasPath(struct Node *rootNew, vector<int>&arr, int x){
	// if root is NULL, there is no path present
	if(rootNew == NULL)
		return false;

	// push the node's value in 'arr'
	arr.push_back(rootNew->data);

	// if it is the required node, return true
	if(rootNew->data == x)
		return true;

	// else check the subtrees
	if(hasPath(rootNew->left, arr, x) || hasPath(rootNew->right, arr, x))
		return true;

	// if required node does not exist in either of right or left subtree, remove
	// current node value from arr and then return false
	arr.pop_back();
	return false;
}

void printPath(struct Node *root, int i, int j){
	// vector to store the path
	vector <int> arr;

	struct Node *rootNew = findInBST(root, i);

	// if required node 'j' is present, then print the path
	if(hasPath(rootNew, arr, j)){
		for(int i = 0; i < arr.size() - 1; i++)
			cout << arr[i] << "->";
		cout << arr[arr.size() - 1] << "\n";
	}

	// if 'x' is not present
	else
		cout << "No path\n";
}

struct Node *insertBST(struct Node *root, int x){
	if(root == NULL)
		return createNewNode(x);
	if(x <= root->data)
		root->left = insertBST(root->left, x);
	else
		root->right = insertBST(root->right, x);

	// return the umchanged pointer after all the operations
	return root;
}

void preorder(struct Node *root){
	if(root == NULL)
		return;
	cout << root->data << " ";
	preorder(root->left);
	preorder(root->right);
}

int main(){
	root = NULL;
	root = insertBST(root, 20);
	insertBST(root, 8);
	insertBST(root, 22);
	insertBST(root, 4);
	insertBST(root, 12);
	insertBST(root, 25);
	insertBST(root, 10);
	insertBST(root, 14);

	cout << "Inserted BST is\n";
	cout << "\n";
	preorder(root);


    printPath(root, 8, 14);
	return 0;
}