// program for boundary traversal of tree (clockwise, starting from root node)
#include <iostream>
using namespace std;

int perimeter[1000];
int perimeterIndex;

struct Node{
	int data;
	struct Node *left;
	struct Node *right;
}*root;

void printLeaves(struct Node* root){
    if ( root ){
        printLeaves(root->left);
 
        // Print it if it is a leaf node
        if ( !(root->left)  &&  !(root->right) ){
            // printf("%d ", root->data);
        	perimeter[perimeterIndex] = root->data;
        	perimeterIndex++;
        }
 
        printLeaves(root->right);
    }
}
 
// A function to print all left boundry nodes, except a leaf node.
// Print the nodes in TOP DOWN manner
void printBoundaryLeft(struct Node* root){
    if (root){
        if (root->left){
            // to ensure top down order, print the node
            // before calling itself for left subtree
            // printf("%d ", root->data);
            perimeter[perimeterIndex] = root->data;
            perimeterIndex++;
            printBoundaryLeft(root->left);
        }
        else if( root->right ){
            // printf("%d ", root->data);
            perimeter[perimeterIndex] = root->data;
            perimeterIndex++;
            printBoundaryLeft(root->right);
        }
        // do nothing if it is a leaf node, this way we avoid
        // duplicates in output
    }
}
 
// A function to print all right boundry nodes, except a leaf node
// Print the nodes in BOTTOM UP manner
void printBoundaryRight(struct Node* root){
    if (root){
        if ( root->right )
        {
            // to ensure bottom up order, first call for right
            //  subtree, then print this node
            printBoundaryRight(root->right);
            //printf("%d ", root->data);
            perimeter[perimeterIndex] = root->data;
            perimeterIndex++;
        }
        else if ( root->left ){
            printBoundaryRight(root->left);
            // printf("%d ", root->data);
            perimeter[perimeterIndex] = root->data;
            perimeterIndex++;
        }
       // do nothing if it is a leaf node, this way we avoid
       // duplicates in output
    }
}
 
 
// A function to do boundary traversal of a given binary tree
void printBoundary (struct Node* root){
    if (root){
        // printf("%d ",root->data);
 		perimeter[perimeterIndex] = root->data;
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
 
// A utility function to create a node
struct Node* newNode( int data ){
    struct Node* temp = new Node;;
 
    temp->data = data;
    temp->left = temp->right = NULL;
 
    return temp;
}
 
// Driver program to test above functions
int main(){
    root = NULL;
    root = newNode(20);
    root->left = newNode(8);
    root->left->left = newNode(4);
    root->left->right = newNode(12);
    root->left->right->left = newNode(10);
    root->left->right->right = newNode(14);
    root->right = newNode(22);
    root->right->right = newNode(25);
 
    printBoundary( root );

    cout << perimeter[0] << " ";
    for(int i = perimeterIndex - 1; i > 0; i--)
    	cout << perimeter[i] << " ";

    cout << "\n";
 
    return 0;
}

