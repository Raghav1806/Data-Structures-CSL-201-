// iteratiev preorder traversal of a BST
#include <iostream>
#include <cstdlib>
using namespace std;

struct treeNode{
  int data;
  struct treeNode *left;
  struct treeNode *right;
}*root;

struct stackNode{
  struct treeNode *address;
  struct stackNode *next;
}*head;

/***** BST Functions *****/

struct treeNode *createNewTreeNode(int x){
  struct treeNode *newptr = new treeNode;
  newptr->data = x;
  newptr->left = NULL;
  newptr->right = NULL;

  return newptr;
}

// BST insertion is done manually in main for simplicity

/***** Stack Functions *****/

struct stackNode *createNewStackNode(struct treeNode *x){
  struct stackNode *newptr = new stackNode;
  newptr->address = x;
  newptr->next = NULL;

  return newptr;
}

void insertStackNode(struct treeNode *x){
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

struct treeNode *stackTopNode(){
  return head->address;
}

void iterativePreorder(struct treeNode *root){
  if(root == NULL)
    return;

  head = NULL;
  insertStackNode(root);

  while(!(stackEmpty())){
    struct treeNode *Node = stackTopNode();
    cout << Node->data << " ";
    deleteStackNode();

    if(Node->right)
      insertStackNode(Node->right);
    if(Node->left)
      insertStackNode(Node->left);
  }
}


int main(){

  root = createNewTreeNode(10);
  root->left        = createNewTreeNode(8);
  root->right       = createNewTreeNode(2);
  root->left->left  = createNewTreeNode(3);
  root->left->right = createNewTreeNode(5);
  root->right->left = createNewTreeNode(2);
  iterativePreorder(root);
  
  return 0;
}

