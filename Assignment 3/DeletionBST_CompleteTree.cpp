// program to completely delete a BST
#include <iostream>
#include <cstdlib>
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

void deleteTree(struct Node *root){
	if(root == NULL)
		return;

	// using postorder traversal of tree (children should be deleted before)
	deleteTree(root->left);
	deleteTree(root->right);

	cout << "Deleting node " << root->data << "\n";
	free(root);
}

int main(){
	root = NULL;
	root = createNewNode(5);
	root->left = createNewNode(3);
	root->right = createNewNode(8);
	root->left->left = createNewNode(2);
	root->left->right = createNewNode(4);
	root->right->left = createNewNode(7);
	root->right->right = createNewNode(10);

	deleteTree(root);
	root = NULL;
	cout << "Tree deleted!\n";
	return 0;
}