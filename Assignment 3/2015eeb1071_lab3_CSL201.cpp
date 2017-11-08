/*

Contains various implementations of BST and AVL Trees:
------------------------------------------------------------------------------
(1) Insertion
(2) Deletion
(3) Total number of leaves
(4) Total number of nodes
(5) Inorder traversal
(6) Preorder traversal
(7) Postorder Traversal
(8) Depth of tree
(9) Width of tree
(10) Lowest common ancestor of two nodes
(11) Printing route/path between two nodes in a tree
(12) Printing perimeter of tree in clockwise fashion, starting from root node
------------------------------------------------------------------------------

Developed by
------------------------------------------------------------------------------
Raghav Sharma 
2015EEB1071

------------------------------------------------------------------------------
Date of Submission: 28/10/2017
------------------------------------------------------------------------------

*/


#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

// global array to store inserted elements
int A[1000], perimeterArray[1000];
int perimeterIndex;

// defined for BST and AVL Tree
struct Node{
	int data, height;
	struct Node *left;
	struct Node *right;
}*root;

// defined for iterative preorder traversal
struct stackNode{
  struct Node *address;
  struct stackNode *next;
}*head;

// function to return a newly created node 
struct Node *createNewNode(int x){
	struct Node *newptr = new Node;
	newptr->data = x;
	newptr->height = 1;
	newptr->left = NULL;
	newptr->right = NULL;

	return newptr;
}

// function to return minimum valued node
struct Node *minValueNode(struct Node *root){
	struct Node *curr = root;

	// loop down to leftmost leaf
	while(curr->left != NULL)
		curr = curr->left;

	return curr;
}

// function to convert input into proper form
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

			i--;

			for(j = 0; j < index; j++)
				number += num[j]*pow(10, index - j - 1);
			number = number*x;
			A[arrayIndex] = number;
			arrayIndex++;			
		}
	}
	
	return arrayIndex;
}

void deleteTree(struct Node *root){
	if(root == NULL)
		return;

	// using postorder traversal of tree 
	deleteTree(root->left);
	deleteTree(root->right);

	free(root);
}

// returns 1 if x occurs in BST, 0 otherwise
int search(struct Node *root, int x){
	// x is not present in BST
	if(root == NULL)
		return 0;
	// x is found
	if(root->data == x)
		return 1;
	if(root->data < x)
		return search(root->right, x);

		return search(root->left, x);
}

// returns total number of leaf nodes in BST
int getLeafCount(struct Node *root){
	if(root == NULL)
		return 0;
	if(root->left == NULL && root->right == NULL)
		return 1;
	else
		return getLeafCount(root->right) + getLeafCount(root->left);
}

int getTreeSize(struct Node *root){
	if(root == NULL)
		return 0;
	else
		return getTreeSize(root->left) + getTreeSize(root->right) + 1;
}

void inorder(struct Node *root){
	if(root == NULL)
		return;
	inorder(root->left);
	cout << root->data << " ";
	inorder(root->right);
}

void postorder(struct Node *root){
	if(root == NULL)
		return;
	postorder(root->left);
	postorder(root->right);
	cout << root->data << " ";
}



// functions for iterative preorder
struct stackNode *createNewStackNode(struct Node *x){
  struct stackNode *newptr = new stackNode;
  newptr->address = x;
  newptr->next = NULL;

  return newptr;
}

void insertStackNode(struct Node *x){
  struct stackNode *newptr = createNewStackNode(x);
  if(head == NULL){
    head = newptr;
    return;
  }

  else{
    struct stackNode *temp = head;
    head = newptr;
    newptr->next = temp;
  }
}

// returns 1 if stack is empty
int stackEmpty(){
  return (head == NULL);
}

void deleteStackNode(){
  if(!stackEmpty()){
    struct stackNode *temp = head;
    head = head->next;
    free(temp);
  }
}

struct Node *stackTopNode(){
  return head->address;
}

void iterativePreorder(struct Node *root){
  if(root == NULL)
    return;

  head = NULL;
  insertStackNode(root);

  while(!(stackEmpty())){
    struct Node *node = stackTopNode();
    cout << node->data << " ";
    deleteStackNode();

    if(node->right)
      insertStackNode(node->right);
    if(node->left)
      insertStackNode(node->left);
  }
}

int findHeight(struct Node *root){
	if(root == NULL)
		return 0;
	else
		return max(findHeight(root->left), findHeight(root->right)) + 1;
}

/***** functions for level order traversal of tree *****/

void printCurrentLevel(struct Node *root, int level){
	if(root == NULL)
		return;
	if(level == 1)
		cout << root->data << " ";
	else if(level > 1){
		printCurrentLevel(root->left, level - 1);
		printCurrentLevel(root->right, level - 1);
	}
}

int height1(struct Node *root){
	if(root == NULL)
		return 0;
	else{
		int leftHeight = height1(root->left);
		int rightHeight = height1(root->right);

		if(leftHeight > rightHeight)
			return leftHeight + 1;
		else
			return rightHeight + 1;
	}
}

void levelOrder(struct Node *root){
	int H = height1(root);
	for(int i = 1; i <= H; i++)
		printCurrentLevel(root, i);

	cout << "\n";
}

struct Node *findLCA(struct Node *root, int i, int j){
	if(root == NULL)
		return NULL;

	// if both i and j are smaller than root->data, traverse to left subtree
	if(root->data > i && root->data > j)
		return findLCA(root->left, i, j);

	// if both i and j are greater than root->data,traverse to right subtree
	if(root->data < i && root->data < j)
		return findLCA(root->right, i, j);

	// if desired location is reached
	return root;
} 

int getWidth(struct Node *root, int level){
	if(root == NULL)
		return 0;
	if(level == 1)
		return 1;

	if(level > 1)
		return getWidth(root->left, level - 1) + getWidth(root->right, level - 1);
}

int getMaxWidth(struct Node *root){
	int maxWidth = 0;
	int width, i;
	int h = height1(root);

	// get width of each level and compare with maxWidth
	for(i = 1; i <= h; i++){
		width = getWidth(root, i);
		if(width > maxWidth)
			maxWidth = width;
	}

	return maxWidth;
}

int findDiameter(struct Node *root){
	if(root == NULL)
		return 0;
	// get the height of left and right subtrees
	int lHeight = height1(root->left);
	int rHeight = height1(root->right);

	// get the diameter of left and right subtrees
	int lDiameter = findDiameter(root->left);
	int rDiameter = findDiameter(root->right);

	// return max of the following:
	// (1) Diameter of left subtree
	// (2) Diameter of right subtree
	// (3) Height of left subtree + height of right subtree + 1

	return max(lHeight + rHeight + 1, max(lDiameter, rDiameter));
}

void printLeaves(struct Node* root){
    if ( root ){
        printLeaves(root->left);
 
        // Print it if it is a leaf node
        if ( !(root->left)  &&  !(root->right) ){
            // printf("%d ", root->data);
        	perimeterArray[perimeterIndex] = root->data;
        	perimeterIndex++;
        }
 
        printLeaves(root->right);
    }
}

void printBoundaryLeft(struct Node* root){
    if (root){
        if (root->left){
            perimeterArray[perimeterIndex] = root->data;
            perimeterIndex++;
            printBoundaryLeft(root->left);
        }
        else if( root->right ){
            perimeterArray[perimeterIndex] = root->data;
            perimeterIndex++;
            printBoundaryLeft(root->right);
        }
    }
}

void printBoundaryRight(struct Node* root){
    if (root){
        if ( root->right ){
            printBoundaryRight(root->right);
            perimeterArray[perimeterIndex] = root->data;
            perimeterIndex++;
        }
        else if ( root->left ){
            printBoundaryRight(root->left);
            perimeterArray[perimeterIndex] = root->data;
            perimeterIndex++;
        }
    }
}

void printBoundary (struct Node* root){
    if (root){
 		perimeterArray[perimeterIndex] = root->data;
 		perimeterIndex++;
        // Print the left boundary in top-down manner.
        printBoundaryLeft(root->left);
 
        // Print all leaf nodes
        printLeaves(root->left);
        printLeaves(root->right);
 
        // Print the right boundary in bottom-up manner
        printBoundaryRight(root->right);
    }
}


/******** BST functions *********/

// function to insert a node in BST
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

// function to delete a node in BST
struct Node *deleteBST(struct Node* root, int data){
	// base case
	if(root == NULL)
		return root;

	// finding the key to be deleted
	// if the key to be deleted is smaller than the root's key
	if(data < root->data)
		root->left = deleteBST(root->left, data);

	// if the key to be deleted is greater than the root's key
	else if(data > root->data)
		root->right = deleteBST(root->right, data);

	// if this is the root to be deleted
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
		root->right = deleteBST(root->right,temp->data);
	}
	return root;
}

/******* AVL Tree functions ******/

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
		return rightRotate(root);

	// right right case
	if(balance < -1 && data > root->right->data)
		return leftRotate(root);

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

	// return the unchanged pointer
	return root;
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
	string S;
	char choice;
	int i, size, Q, flag, check;

	flag =  0;

	// flag = 0 means no tree has yet been alloted
	// flag = 1 means we are working on BST
	// flag = 2 means we are working on AVL tree

	cin >> Q;
	
	while(Q--){

		// to remove buffer in getline function
		cin >> ws;
		getline(cin, S);
		size = convertIntoArray(S);

		// for debugging purposes
		// cout << "size = " << size << "\n"; 
		
		choice = S[0];

		if(choice == 'T'){
			// perform operations of BST
			// delete previous tree (if any)
			flag = 1;
			deleteTree(root);

			root = NULL;
			for(i = 0; i < size; i++){
				if(A[i] > 0)
					// add elements to BST
					root = insertBST(root, A[i]);
				if(A[i] < 0){
					A[i] = A[i]*(-1);
					root = deleteBST(root, A[i]);
				}
			}

			// for debugging purposes
			// cout << "The inorder traversal of final BST is\n";
			// inorder(root);
		}

		else if(choice == 'H'){
			// perform AVL tree operations
			// delete previous tree (if any)
			flag = 2;
			deleteTree(root);
			
			root = NULL;
			for(i = 0; i < size; i++){
				if(A[i] > 0)
					// add elements to AVL tree
					root = insertAVL(root, A[i]);
				if(A[i] < 0){
					A[i] = A[i]*(-1);
					root = deleteAVL(root, A[i]);
				}
			}

			// for debugging purposes
			// cout << "The inorder traversal of final AVL tree is\n";
			// inorder(root);
		}


		else if(choice == 'A'){
			// insert Nodes in tree

			if(flag == 1){
				// insert nodes in BST
				 for(i = 0; i < size; i++){
				//		cout << A[i] << "***\n";

					if(A[i] > 0)
						// add elements in BST
						root = insertBST(root, A[i]);
				}
			}

			else if(flag == 2){
				// insert nodes in AVL tree
				for(i = 0; i < size; i++){
					if(A[i] > 0)
						// add elements in AVL tree
						root = insertAVL(root, A[i]);
				}
			}
		}

		else if(choice == 'F'){
			// search for a root in tree
			check = search(root, A[0]);
			if(check == 1)
				cout << "Yes\n";
			else
				cout << "No\n";
		}

		else if(choice == 'U'){
			// delete nodes from tree
			if(flag == 1){
				// delete nodes from BST
				for(i = 0; i < size; i++){
					if(A[i] > 0)
						root = deleteBST(root, A[i]);
				}
			}

			else if(flag == 2){
				// delete nodes from AVL tree
				for(i = 0; i < size; i++){
					if(A[i] > 0)
						root = deleteAVL(root, A[i]);
				}
			}
		}

		else if(choice == 'Q'){
			// print number of leafs in the tree
			cout << getLeafCount(root) << "\n";
		}

		else if(choice == 'N'){
			// print total number of nodes in the tree
			cout << getTreeSize(root) << "\n";
		}

		else if(choice == 'P'){
			// iterative preorder traversal of tree
			iterativePreorder(root);
			cout << "\n";
		}

		else if(choice == 'I'){
			// inorder traversal of tree
			inorder(root);
			cout << "\n";
		}

		else if(choice == 'S'){
			// postorder traversal of tree
			postorder(root);
			cout << "\n";
		}

		else if(choice == 'L'){
			// level order traversal of tree
			levelOrder(root);
			cout << "\n";
		}

		else if(choice == 'D'){
			// find depth of the tree
			cout << findHeight(root) << "\n";
		}

		else if(choice == 'W'){
			// find the width of the tree
			cout << getMaxWidth(root) << "\n";
		}

		else if(choice == 'C'){
			// find the lowest common ancestor of two nodes
			int i = A[0];
			int j = A[1];

			if(search(root, i) == 0 || search(root, j) == 0)
				cout << "-1\n";
			else{
				struct Node *temp = findLCA(root, i, j);

				if(temp == NULL)
					cout << "-1\n";
				else
					cout << temp->data << "\n";
			}
		}

		else if(choice == 'R'){
			int i = A[0];
			int j = A[1];

			int checkSource = search(root, i);
			int checkDestination = search(root, j);

			if(checkSource == 0){
				cout << "Source does not exist\n";
				continue;
			}

			else if(checkDestination == 0){
				cout << "Destination does not exist\n";
				continue;
			}

			else if(i == j){
				cout << i << " Reached " << j << "\n";
				continue;
			}

			else{
				cout << "This part was not executed!\n";
			}
		}

		else if(choice == 'X'){
			// print length of diameter of tree
			cout << findDiameter(root) << "\n";
		}

		else if(choice == 'Y'){
			// print the perimeter in clockwise manner, starting from root
			perimeterIndex = 0;

			printBoundary(root);

			cout << perimeterArray[0] << " ";

			for(int i = perimeterIndex - 1; i > 0; i--)
				cout << perimeterArray[i] << " ";

			cout << "\n";
		}	
	}
	return 0;
}
