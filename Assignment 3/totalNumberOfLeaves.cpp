// program to print total number of leaves in a BST
#include <iostream>
using namespace std;

struct Node{
   int data;
   struct Node *left;
   struct Node *right;
 }*root; 

 int getLeafCount(struct Node* root){
  if(root == NULL)       
    return 0;
  if(root->left == NULL && root->right==NULL)      
    return 1;            
  else
    return getLeafCount(root->left) + getLeafCount(root->right);      
}
 
/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct Node* newNode(int data){
  struct Node* node = new Node;
  node->data = data;
  node->left = NULL;
  node->right = NULL;
   
  return(node);
}
 
/*Driver program to test above functions*/ 
int main(){
  root = NULL;
  /*create a tree*/ 
  root = newNode(1);
  root->left        = newNode(2);
  root->right       = newNode(3);
  root->left->left  = newNode(4);
  root->left->right = newNode(5);    
   
  /*get leaf count of the above created tree*/
  printf("Leaf count of the tree is %d", getLeafCount(root));
   
  return 0;
}