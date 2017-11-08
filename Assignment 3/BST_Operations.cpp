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

// function to insert a node in BST
struct Node *insertBST(struct Node *root, int x){
	if(root == NULL)
		return createNewNode(x);
	if(x <= root->data)
		root->left = insertBST(root->left, x);
	else if(x > root->data)
		root->right = insertBST(root->right, x);
		
	return root;			
}

// for debugging
void inorder(struct Node *root){
	if(root != NULL){
		inorder(root->left);
		cout << root->data << " ";
		inorder(root->right);
	}
	
	cout << "\n";
} 

// function to return minimum valued node
struct Node *minValueNode(struct Node *root){
	struct Node *curr = root;
	
	// loop down to leftmost leaf
	while(curr->left != NULL)
		curr = curr->left;
	return curr;	
}

// function to delete a node in BST
struct Node* deleteNode(struct Node* root, int data)
{
    // base case
    if (root == NULL) return root;
 
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (data < root->data)
        root->left = deleteNode(root->left, data);
 
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }
 
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct Node* temp = minValueNode(root->right);
 
        // Copy the inorder successor's content to this node
        root->data = temp->data;
 
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int main(){

	root = NULL;
	int i, size;
	cout << "Enter the size of array\n";
	cin >> size;
	int A[size];
	cout << "Enter the elements of array\n";
	for(i = 0; i < size; i++){
		cin >> A[i];
		if(A[i] > 0)
			// add elements to BST
			root = insertBST(root, A[i]);
		if(A[i] < 0){
			// delete element from BST
			A[i] = A[i]*(-1);
			root = deleteNode(root, A[i]);
		}	
	}
	
	cout << "The inorder traversal of final BST is\n";
	inorder(root);
		
	return 0;	
}
