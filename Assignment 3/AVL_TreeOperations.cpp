// program for basic operations in AVL Tree
#include <iostream>
#include <cstdlib>
using namespace std;

struct Node{
	int data;
	struct Node *left;
	struct Node *right;
	int height;
}*root;

struct Node *createNewNode(int x){
	struct Node *newptr = new Node;
	newptr->data = x;
	newptr->left = NULL;
	newptr->right = NULL;
	newptr->height = 1;

	return newptr;
}

void inorder(struct Node *root){
	if(root == NULL)
		return;
	else{
		inorder(root->left);
		cout << root->data << " ";
		inorder(root->right);
	}

	cout << "\n";
}

int max(int a, int b){
	if(a >= b)
		return a;
	else
		return b;
}

int height(struct Node *root){
	if(root == NULL)
		return 0;
	else
		return root->height;
}

int getBalance(struct Node *root){
	if(root == NULL)
		return 0;
	else
		return height(root->left) - height(root->right);
}

struct Node *rightRotate(struct Node *y){
	struct Node *x = y->left;
	struct Node *T2 = x->right;

	// perform rotation
	x->right = y;
	y->left = T2;

	// update heights
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	// return new root
	return x;
}

struct Node *leftRotate(struct Node *x){
	struct Node *y = x->right;
	struct Node *T2 = y->left;

	// perform rotation
	y->left = x;
	x->right = T2;

	// update heights
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	// return new root
	return y;
}

struct Node *insertAVL(struct Node *root, int data){
	int balance;

	// perform normal BST insertion
	if(root == NULL)
		return createNewNode(data);
	if(data <= root->data)
		root->left = insertAVL(root->left, data); 
	else if(data > root->data)
		root->right = insertAVL(root->right, data);

	// update the height of ancestor node
	root->height = 1 + max(height(root->left),height(root->right));

	// get the balance factor of this ancestor node
	balance = getBalance(root);

	// if this node is unbalanced, then 4 cases are possible

	// left left case
	if(balance > 1 && data < root->left->data)
		return leftRotate(root);

	// right right case
	if(balance > 1 && data > root->right->data)
		return rightRotate(root);

	// left right case
	if(balance > 1 && data > root->left->data){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// right left case
	if(balance < -1 && data < root->right->data){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	// return the unchanged pointers
	return root;
}

struct Node *minValueNode(struct Node *root){
	struct Node *curr = root;

	// loop down to find smallest node
	while(curr->left != NULL)
		curr = curr->left;

	return curr;
}

struct Node *deleteAVL(struct Node *root, int data){
	int balance;
	// perform standard BST delete
	if(root == NULL)
		return root;

	// if the key is in left subtree
	if(data < root->data)
		root->left = deleteAVL(root->left, data);

	// if the key is in right subtree
	if(data > root->data)
		root->right = deleteAVL(root->right, data);

	// if this is the node to be deleted
	else{

		// node with only one child or no child
		if(root->left == NULL){
			struct Node *temp = root->right;
			free(root);
			return temp;
		}

		else if(root->right == NULL){
			struct Node *temp = root->left;
			free(root);
			return temp;
		}

		// node with two children
		struct Node *temp = minValueNode(root->right);

		// copy the inorder successor's content to this node
		root->data = temp->data;

		// delete the inorder successor
		root->right = deleteAVL(root->right,temp->data);
	}

	// return root;

	// update the height of current node
	root->height = 1 + max(height(root->left), height(root->right));

	// get the balanced factor from this node (bottomm up manner)
	balance = getBalance(root);

	// if this node is unbalanced, there are 4 possible cases

	// left left case
	if(balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);


	// right right case
	if(balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	// left right case
	if(balance > 1 && getBalance(root->left) < 0){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// right left case
	if(balance < -1 && getBalance(root->right) > 0){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

int main(){
	root = NULL;
	int size, i;
	cout << "Enter the size of array\n";
	cin >> size;
	int A[size];
	cout << "Enter the elements of array\n";

	for(i = 0; i < size; i++){
		cin >> A[i];
		if(A[i] > 0)
			root = insertAVL(root, A[i]);
		else if(A[i] < 0){
			A[i] = -1*A[i];
			root = deleteAVL(root, A[i]);
		}
	}

	cout << "The inorder traversal of tree is\n";

	inorder(root);

	return 0;
}