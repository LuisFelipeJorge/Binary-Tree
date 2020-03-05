#include <stdio.h> //Standard header for C language.
#include <stdlib.h>// Contains functions as malloc, that help to dynamically allocate the memory.
#include <stdbool.h> // Allow us to work with boolean type
#include <limits.h> // contains the INT_MIN value.

//Definition of the data structure
///////////////////////////////////////////////////////
struct Node{
  /*
  A binary tree is made up of nodes that carry three pieces of information.
  Data and 2 pointers for other nodes.
  We could see the nodes as cells with sub-divisions
         *****************       The middle cell stores the data that we want to save
    <----*ptr* Data * ptr*---->  the others cells stores the pointers that represent the links
         *****************       other nodes.
  */
  int key;                  //represents the data we want to store, in this case, it's an integer.
  struct Node *left,*right; // pointes that link to other nodes .
  int height;// Stores the node height value, it will help in the process of balancing the tree.
};

//Definition of the functions that will be used in the program
///////////////////////////////////////////////////////

struct Node* createNode(int new_key); // Function to allocate extra memory for a new node.
struct Node* insert(struct Node* root_node,int new_key); // Function to insert a new element in the tree.
bool search(struct Node* root_node,int key);// Function to check whether an element is present in the tree or not.
void cleanTree(struct Node** root_node);// Function to free the memory allocated for the tree.
int findMinimum(struct Node* root_node); // Find the minimum value in the binary search tree.
int findMaximum(struct Node* root_node);// Find the maximum value in the binary search tree.
int getmax(int a, int b);  // Utility function to obtain the maximum value between two numbers
int height(struct Node* root_node); // Function to find the height of a node.

//Functions to balance the tree

struct Node* rotateRight(struct Node* x); // Function to execute right rotation
struct Node* rotateLeft(struct Node* y);
struct Node* rr(struct Node* root_node);
struct Node* ll(struct Node* root_node);
struct Node* rl(struct Node* root_node);
struct Node* lr(struct Node* root_node);
int balanceFactor(struct Node* root_node);

//Functions to print the tree
void preorder(struct Node* root_node);
void inorder(struct Node* root_node);
void postorder(struct Node* root_node);

///////////////////////////////////////////////////////

int main(int argc, char const *argv[]) {
  struct Node* root = NULL;
  int h = height(root);
  printf("height : %d \n",h);
  root = insert(root,25);
  root = insert(root,15);
  root = insert(root,30);
  h = height(root);
  printf("height : %d \n",h);
  root = insert(root,12);
  root = insert(root,20);
  root = insert(root,27);
  root = insert(root,33);
  h = height(root);
  printf("height : %d \n",h);
    if (search(root,33)) {
    printf("Element found \n");
  }else{
    printf("Element not found\n");
  }
  if (search(root,50)) {
    printf("Element found \n");
  }else{
    printf("Element not found\n");
  }
  int min = findMinimum(root);
  printf("Minimun value : %d \n",min);
  int max = findMaximum(root);
  printf("Maximum value : %d \n",max);
  root = insert(root, 11); // creating an imbalance
  root = insert(root,9);
  root = insert(root,60);
  root = insert(root,45);
  // testing the print functions
  preorder(root);
  printf("\n");
  inorder(root);
  printf("\n");
  postorder(root);
  printf("\n");

  cleanTree(&root);
  min = findMinimum(root);
  printf("Minimun value : %d \n",min);
  max = findMaximum(root);
  printf("Maximum value : %d \n",max);
  return 0;
}

///////////////////////////////////////////////////////

struct Node* createNode(int new_key){
  struct Node* temp = (struct Node*)malloc(sizeof(struct Node)); // temporary variable to help to allocate the memory
  temp->key = new_key;      // Store the data
  temp->right = temp->left = NULL; // new node do not have childs at first moment
  temp->height = 0; // leaf node height is zero .
  return temp; // return the new node
}

///////////////////////////////////////////////////////
/*
Binary trees are recursive structures, so we will generally choose this approach
to solve problems in our functions
*/
struct Node* insert(struct Node* root_node,int new_key){

  //Inserting the new element
  if (root_node == NULL) {
    // In the case that the tree is empty:
    root_node = createNode(new_key);
    return root_node;
  }else if (new_key <= root_node->key) {
    // In this case, the value of the new element is less than the value at the root.
    // Therefore, we must place them in the left subtree.
    root_node->left = insert(root_node->left,new_key);
  }else{
    // In this case, the value of the new element is greater than the value at the root.
    // Therefore, we must place them in the right subtree.
    root_node->right = insert(root_node->right,new_key);
  }

  // Updating the height of the tree
  root_node->height = height(root_node);

  //Check whether the tree is unbalanced or not. We need to check the reason for the imbalance.
  //After finding the right case, we apply the right type of rotation
  if ((balanceFactor(root_node) > 1) && (new_key < root_node->left->key)) {
    //LeftLeft Case
    root_node = ll(root_node);
  }else if ((balanceFactor(root_node) > 1) && (new_key > root_node->left->key)) {
    //LeftRight Case
    root_node = lr(root_node);
  }else if ((balanceFactor(root_node) < -1) && (new_key > root_node->right->key)) {
    //RightRight Case
    root_node = rr(root_node);
  }else if ((balanceFactor(root_node) < -1) && (new_key < root_node->right->key)) {
      //Rightleft Case
      root_node = rl(root_node);
  }

  return root_node;
}

///////////////////////////////////////////////////////

bool search(struct Node* root_node,int key){

  if (root_node == NULL ) {
    // Base case: the element does not belong to the tree or the tree is empty.
    return false;
  }else if (root_node->key == key) {
    // The element was found
    return true;
  }else if (key <= root_node->key) { // the element we are trying to find is smaller than the root value.
    // Keep searching in the left subtree.
    return search(root_node->left,key);
  }else{  //the element we are trying to find if greater than the root value.
    // Keep searching in the right subtree.
    return search(root_node->right,key);
  }
}

///////////////////////////////////////////////////////

void cleanTree(struct Node** root_node){
  if (*root_node == NULL) { // Empty tree
    return; // Do nothing
  }else{
    struct Node *aux = (*root_node);
    // Delete the subtrees
    cleanTree(&aux->left);
    cleanTree(&aux->right);
    free(aux);
  }
  *root_node = NULL; //return a NULL pointer
}

///////////////////////////////////////////////////////

int findMinimum(struct Node* root_node){

  if (root_node == NULL) {
    printf("Empty Tree\n");
    return INT_MIN;
  }else{
    // To find the minimum value of the tree, we need to go all the way to the left subtree of each node,
    // the minimum value will be in the leftmost position of the tree.
    while(root_node->left != NULL){ // check if the node has a left child
      root_node = root_node->left;
    }
    return root_node->key;
  }
}

///////////////////////////////////////////////////////

int findMaximum(struct Node* root_node){

  if (root_node == NULL) {
    printf("Empty Tree\n");
    return INT_MAX;
  }else{
    // To find the maximum value of the tree, we need to go all the way to the right subtree of each node,
    // the maximum value will be in the rightmost position of the tree.
    while(root_node->right != NULL){ // check if the node has a right child
      root_node = root_node->right;
    }
    return root_node->key;
  }

}

///////////////////////////////////////////////////////

int getmax(int a, int b){
  // function to get the maximum value between two numbers
  return (a > b)? a : b; //ternary operator
  // Syntax: (Condition)?true_value:false_value
}
///////////////////////////////////////////////////////

int height(struct Node*root_node){
  // I will use the definition of the height of a node as the number of edges on the longest path from the node to a leaf.
  // Some people define height as the number of nodes on that path.
  // This will only make a difference when we define the base case for our recursive approach.
  //Base case : An empty tree or a leaf node
  if (root_node == NULL) {
    return -1;// -1 because we define the height of a leaf node as 0.
  }else{
    int rightH = height(root_node->right); // height of the right subtree.
    int leftH  = height(root_node->left); // height of the left subtree.
    // We must obtain the maximum value between these two heights.
    // The height of the input node will be equal to the maximum value plus 1.
    return (getmax(rightH,leftH) + 1);
  }
}

///////////////////////////////////////////////////////

//ROTATIONS

struct Node* rotateRight(struct Node* x){

  struct Node *y,*t2; //auxiliary variable to help reorganize Links.
  y = x->left;
  t2 = y->right;// t2 is a generic subtree
  //Rotation
  y->right = x;
  x->left = t2;
  // Updating the heights og the subtrees
  x->height = height(x);
  y->height = height(y);

  return y; // y is the new root after the rotation.
}

struct Node* rotateLeft(struct Node* y){

  struct Node *x,*t2; //auxiliary variable to help reorganize Links.
  x = y->right;
  t2 = x->left; // t2 is a generic subtree
  //Rotation
  x->left = y;
  y->right = t2;
  // Updating the heights of the subtrees
  x->height = height(x);
  y->height = height(y);

  return x; // x is the new root after the rotation.
}

///////////////////////////////////////////////////////

//Cases for Simple or Double ROTATIONS

// Unbalanced RightRight

struct Node* rr(struct Node* root_node){
  //Simple Rotation
  return rotateLeft(root_node);

}

// Unbalanced LeftLeft

struct Node* ll(struct Node* root_node){
  //Simple Rotation
  return rotateRight(root_node);
}

// Unbalanced LeftRight

struct Node* lr(struct Node* root_node){
  // Double Rotation
  root_node->left = rotateLeft(root_node->left);
  root_node = rotateRight(root_node);
  return root_node;
}

// Unbalanced RightLeft

struct Node* rl(struct Node* root_node){
  // Double Rotation
  root_node->right = rotateRight(root_node->right);
  root_node = rotateLeft(root_node);
  return root_node;
}

///////////////////////////////////////////////////////

int balanceFactor(struct Node* root_node){
  if(root_node == NULL){
    // Empty tree or leaf node
    return 0;
  }else{
    return (height(root_node->left) - height(root_node->right));
    // The balance factor is the difference between the height
    // of the left subtree nd the right subtree
  }
}

///////////////////////////////////////////////////////

void preorder(struct Node* root_node) {
  //Base case to stop the recursion.
  if (root_node == NULL) {
    return;
  }else{
    printf(" %d ",root_node->key );// First we access the data stored in the node.
    preorder(root_node->left);// After we visit all the elements in the left subtree.
    preorder(root_node->right);// Then we visit the right subtree.
  }
}

///////////////////////////////////////////////////////

void inorder(struct Node* root_node) {
  //Base case to stop the recursion.
  if (root_node == NULL) {
    return;
  }else{
    inorder(root_node->left);// First we visit all the elements in the left subtree.
    printf(" %d ",root_node->key );// After we access the data stored in the root.
    inorder(root_node->right);// Then we visit the right subtree.
  }
}

///////////////////////////////////////////////////////

void postorder(struct Node* root_node) {
  //Base case to stop the recursion.
  if (root_node == NULL) {
    return;
  }else{
    postorder(root_node->left);// First we visit all the elements in the left subtree.
    postorder(root_node->right);// After we visit the right subtree.
    printf(" %d ",root_node->key );// Then we access the data stored in the root.
  }
}
