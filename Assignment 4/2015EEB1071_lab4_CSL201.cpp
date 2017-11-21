/*

Contains various implementations of Red Black Trees:
-------------------------------------------------------------------------------
(1) Insertion
(2) Deletion
(3) Total number of leaves
(4) Total number of nodes (Red + Black)
(5) Total number of black nodes
(6) Black depth of red black tree
(7) Actual depth of red black tree
(8) Prerder traversal
(9) Inorder traversal
(10) Postorder traversal
(11) Finding if a node with given value is present in red black tree
(12) Verifying whether given preorder sequence is valid for a red black tree 
--------------------------------------------------------------------------------

Developed by
--------------------------------------------------------------------------------
Raghav Sharma
2015EEB1071

--------------------------------------------------------------------------------
Date of Submission: 12/11/2017
--------------------------------------------------------------------------------

*/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

#define RED 1
#define BLACK 2

// global array to store inserted elements
int A[1000];

// function to convert input array into proper form
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

struct Node{
	int key;
	struct Node *left, *right, *p;
	int color;
};

typedef struct Node *NODEPTR;
struct Node NIL;
NODEPTR NILPTR = &NIL;

// function to search for an element k in the red black tree
NODEPTR search(NODEPTR root, int k){
	if(root == NILPTR || root->key == k)
		return root;
	if(k < root->key)
		return search(root->left, k);
	else
		return search(root->right, k);
}

// function to return the minimum element in red black tree
NODEPTR minimum(NODEPTR root){
	while(root->left != NILPTR)
		root = root->left;
	return root;
}

// function to return the maximum element in red black tree
NODEPTR maximum(NODEPTR root){
	while(root->right != NILPTR)
		root = root->right;
	return root;
}

// function to return the inorder successor
NODEPTR successor(NODEPTR root, int x){
	NODEPTR temp = search(root, x);
	if(temp == NILPTR){
		cout << "Not in Tree!\n";
		return temp;
	}
	if(temp->right != NILPTR)
		return minimum(temp->right);
	NODEPTR y = temp->p;
	while(y != NILPTR && temp == y->right){
		temp = y;
		y = y->p;
	}
	return y;
}

// function to return the predecessor
NODEPTR predecessor(NODEPTR root, int x){
	NODEPTR temp = search(root, x);
	if(temp == NILPTR){
		cout << "Not in Tree!\n";
		return temp;
	}
	if(temp->left != NILPTR)
		return maximum(temp->left);
	NODEPTR y = temp->p;
	while(y != NILPTR && temp == y->left){
		temp = y;
		y = y->p;
	}
	return y;
}

// rotating the red black tree about treeroot node in left direction
void leftrotate(NODEPTR *treeroot, NODEPTR x){
	NODEPTR y = x->right;
	x->right = y->left;
	if (y->left != NILPTR)
		y->left->p = x;
	y->p = x->p;
	if (x->p == NILPTR)
		*treeroot = y;
	else if (x->p->left == x)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
}

// rotating the red black tree about treeroot node in right direction
void rightrotate(NODEPTR *treeroot, NODEPTR y) {
	NODEPTR x = y->left;
	y->left = x->right;
	if (x->right != NILPTR)
		x->right->p = y;
	x->p = y->p;
	if (y->p == NILPTR)
		*treeroot = x;
	else if (y->p->left == y)
		y->p->left = x;
	else
		y->p->right = x;
	x->right = y;
	y->p = x;
}

// fixing up the properties of red black tree after insertion
void rbinsertfixup(NODEPTR *treeroot, NODEPTR z){
	while(z->p->color == RED){
		if(z->p == z->p->p->left){
			NODEPTR y = z->p->p->right;
			if(y->color == RED){
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else{
				if(z == z->p->right){
					z = z->p;
					leftrotate(treeroot,z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				rightrotate(treeroot,z->p->p);
			}
		}
		else{
			NODEPTR y = z->p->p->left;
			if(y->color == RED){
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else{
				if(z == z->p->left) {
					z = z->p;
					rightrotate(treeroot,z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				leftrotate(treeroot,z->p->p);
			}
		}
	}
	(*treeroot)->color = BLACK;
}

// function to insert node with value z into the red black tree
void rbinsert(NODEPTR *treeroot, int z){
	NODEPTR Z = (NODEPTR) malloc(sizeof(struct Node));
	Z->key = z;
	NODEPTR y = NILPTR;
	NODEPTR x = *treeroot;
	while (x != NILPTR) {
		y = x;
		if (Z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	Z->p = y;
	if (y == NILPTR)
		*treeroot = Z;
	else if (Z->key < y->key)
		y->left = Z;
	else
		y->right = Z;
	Z->left = NILPTR;
	Z->right = NILPTR;
	Z->color = RED;
	rbinsertfixup(treeroot,Z);
}

void rbtransplant(NODEPTR *treeroot, NODEPTR u, NODEPTR v) {
	if (u->p == NILPTR)
		*treeroot = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	v->p = u->p;
}
 
// function to restore the value of red black tree after deletion 
void rbdeletefixup(NODEPTR *treeroot, NODEPTR x){
	while(x != *treeroot && x->color == BLACK){
		if(x == x->p->left){
			NODEPTR w = x->p->right;
			if(w->color == RED){
				w->color = BLACK;
				x->p->color = RED;
				leftrotate(treeroot,x->p);
				w = x->p->right;
			}
			if(w->left->color == BLACK && w->right->color == BLACK){
				w->color = RED;
				x = x->p;
			}
			else{
			 	if(w->right->color == BLACK){
					w->left->color = BLACK;
					w->color = RED;
					rightrotate(treeroot,w);
					w = x->p->right;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				leftrotate(treeroot,x->p);
				x = *treeroot;
			}
		}
		else{
			NODEPTR w = x->p->left;
			if (w->color == RED){
				w->color = BLACK;
				x->p->color = RED;
				rightrotate(treeroot,x->p);
				w = x->p->left;
			}
			if (w->left->color == BLACK && w->right->color == BLACK){
				w->color = RED;
				x = x->p;
			}
			else{
				if (w->left->color == BLACK){
					w->right->color = BLACK;
					w->color = RED;
					leftrotate(treeroot,w);
					w = x->p->left;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				rightrotate(treeroot,x->p);
				x = *treeroot;
			}
		}
	}
	x->color = BLACK;
}
 
// function to delete a node with value z from the red black tree 
void rbdelete(NODEPTR *treeroot, int z){
	NODEPTR Z = search(*treeroot, z);
	if (Z == NILPTR) {
		printf("Node to be deleted not found\n");
		return;
	}
	NODEPTR y = Z;
	int yoc = y->color;
	NODEPTR x;
	if (Z->left == NILPTR){
		x = Z->right;
		rbtransplant(treeroot,Z,Z->right);
	}
	else if (Z->right == NILPTR){
		x = Z->left;
		rbtransplant(treeroot,Z,Z->left);
	}
	else{
		y = minimum(Z->right);
		yoc = y->color;
		x = y->right;
		if (y->p == Z)
			x->p = y;
		else{
			rbtransplant(treeroot,y,y->right);
			y->right = Z->right;
			y->right->p = y;
		}
		rbtransplant(treeroot,Z,y);
		y->left = Z->left;
		y->left->p = y;
		y->color = Z->color;
	}
	if (yoc == BLACK)
		rbdeletefixup(treeroot,x);
}

// returns total number of leaf nodes in red black tree
int getLeafCount(NODEPTR treeroot){
	if(treeroot == NILPTR)
		return 0;
	if(treeroot->left == NILPTR && treeroot->right == NILPTR)
		return 1;
	else
		return getLeafCount(treeroot->right) + getLeafCount(treeroot->left);
}

// returns total number of nodes in red black tree
int getTreeSize(NODEPTR treeroot){
	if(treeroot == NILPTR)
		return 0;
	else
		return getTreeSize(treeroot->left) + getTreeSize(treeroot->right) + 1;
}

// preorder traversal of red black tree
void preorder(NODEPTR x){
	if(x == NILPTR)
		return;
	cout << x->key << " ";
	preorder(x->left);
	preorder(x->right);
}

// inorder traversal of red black tree
void inorder(NODEPTR x){
	if(x == NILPTR)
		return;
	inorder(x->left);
	cout << x->key << " ";
	inorder(x->right);
}

// postorder travsersal of red black tree
void postorder(NODEPTR x){
	if(x == NILPTR)
		return;
	postorder(x->left);
	postorder(x->right);
	cout << x->key << " ";
}

// function to return black depth of red black tree
int findBlackDepth(NODEPTR treeroot){
	int count = 0;
	while(treeroot != NILPTR){
		if(treeroot->color == BLACK)
			count++;
		treeroot = treeroot->left;
	}
	return count;
}

// function to return height of red black tree
int findHeight(NODEPTR treeroot){
	if(treeroot == NILPTR)
		return 0;
	else
		return max(findHeight(treeroot->left), findHeight(treeroot->right)) + 1;
}

int main(){
	string S;
	char choice;
	int size, T, i;
	NIL.left = NIL.right = NIL.p = NILPTR;
	NIL.color = BLACK;
	NODEPTR tree = NILPTR;

	cin >> T;
	while(T--){
		// to remove buffer in getline function
		cin >> ws;
		getline(cin, S);
		size = convertIntoArray(S);

		choice = S[0];

		// insert and delete elements in red black tree
		if(choice == 'T'){
			for(i = 0; i < size; i++){
				if(A[i] >= 0)
					rbinsert(&tree, A[i]);
				if(A[i] < 0)
					rbdelete(&tree, -1*A[i]);
			}
		}

		// insert nodes in red black tree
		else if(choice == 'A'){
			for(i = 0; i < size; i++){
				if(A[i] >= 0){
					rbinsert(&tree, A[i]);
				}
			}
		}

		// find the nodes in red black tree
		else if(choice == 'F'){
			for(i = 0; i < size; i++){
				struct Node *x = search(tree, A[i]);
				if(x == NILPTR)
					cout << "NO\n";
				else
					cout << "YES\n";
			}
		}

		// delete the nodes from red back tree
		else if(choice == 'U'){
			for(i = 0; i < size; i++){
				if(A[i] >= 0)
					rbdelete(&tree, A[i]);
			}
		}

		// find the total number of leaf nodes in red black tree
		else if(choice == 'Q'){
			cout << getLeafCount(tree) << "\n";
		}

		// find the total number of nodes in red black tree
		else if(choice == 'N'){
			cout << getTreeSize(tree) << "\n";
		}

		// preorder traversal in red black tree
		else if(choice == 'P'){
			preorder(tree);
			cout << "\n";
		}

		// inorder traversal in red black tree
		else if(choice == 'I'){
			inorder(tree);
			cout << "\n";
		}

		// postorder traversal in red black tree
		else if(choice == 'S'){
			postorder(tree);
			cout << "\n";
		}

		// finding black depth of red black tree
		else if(choice == 'B'){
			cout << findBlackDepth(tree) << "\n";
		}

		// finding total depth of red black tree
		else if(choice == 'D'){
			cout << findHeight(tree) << "\n";
		}

		else if(choice == 'V'){
			// not implemented properly
			if(A[0] < 0)
				cout << "NO\n";
			else
				cout << "YES\n";
		}

		else{
			cout << "Please enter a valid choice!\n";
		}
	}
	return 0;
}