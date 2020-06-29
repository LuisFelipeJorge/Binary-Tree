// Import the header file

#include "avlTree.h"

// Functions Definitions
///////////////////////////////////////////////////////

Node* createNode(int new_key){
  Node* temp = (Node*)malloc(sizeof(Node)); // temporary variable to help to allocate the memory
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
Node* insert(Node* root_node,int new_key){

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

bool search(Node* root_node,int key){

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

void cleanTree(Node** root_node){
  if (*root_node == NULL) { // Empty tree
    return; // Do nothing
  }else{
    Node *aux = (*root_node);
    // Delete the subtrees
    cleanTree(&aux->left);
    cleanTree(&aux->right);
    free(aux);
  }
  *root_node = NULL; //return a NULL pointer
}

///////////////////////////////////////////////////////

int findMinimum(Node* root_node){

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

int findMaximum(Node* root_node){

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

int height(Node*root_node){
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

Node* rotateRight(Node* x){

  Node *y,*t2; //auxiliary variable to help reorganize Links.
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

Node* rotateLeft(Node* y){

  Node *x,*t2; //auxiliary variable to help reorganize Links.
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

Node* rr(Node* root_node){
  //Simple Rotation
  return rotateLeft(root_node);

}

// Unbalanced LeftLeft

Node* ll(Node* root_node){
  //Simple Rotation
  return rotateRight(root_node);
}

// Unbalanced LeftRight

Node* lr(Node* root_node){
  // Double Rotation
  root_node->left = rotateLeft(root_node->left);
  root_node = rotateRight(root_node);
  return root_node;
}

// Unbalanced RightLeft

Node* rl(Node* root_node){
  // Double Rotation
  root_node->right = rotateRight(root_node->right);
  root_node = rotateLeft(root_node);
  return root_node;
}

///////////////////////////////////////////////////////

int balanceFactor(Node* root_node){
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

void preorder(Node* root_node) {
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

void inorder(Node* root_node) {
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

void postorder(Node* root_node) {
  //Base case to stop the recursion.
  if (root_node == NULL) {
    return;
  }else{
    postorder(root_node->left);// First we visit all the elements in the left subtree.
    postorder(root_node->right);// After we visit the right subtree.
    printf(" %d ",root_node->key );// Then we access the data stored in the root.
  }
}

///////////////////////////////////////////////////////

Node* deleteNode(Node* root_node,int key){
  // First, we need to perform a standard BST deletion
  if (root_node == NULL) {
    // Empty tree
    return root_node;
  }
  //If the value of the key we want to delete is less than the value of the current key on the root node,
  // we must look in the left subtree.
  if (key < root_node->key) {
    root_node->left = deleteNode(root_node->left,key);
  }else if (key > root_node->key) {
    //If the value of the key we want to delete is greater than the value of the current key on the root node,
    // we must look in the right subtree.
    root_node->right = deleteNode(root_node->right,key);
  }else{
    // root->key == key , we find the element
      // We must discover if node has children.
      if ((root_node->left == NULL) || (root_node->right == NULL)){
        Node* temp = (root_node->left)? (root_node->left):(root_node->right);
        // Syntax: (Condition)?true_value:false_value
        // temp helps to change the reference of the node to be deleted
        if (temp == NULL) {// NO child case
          temp = root_node;
          root_node = NULL;
        }else{
          // One child case
          *root_node = *temp; // pass the reference of the non-empty child
          free(temp);
        }
      }else{
        // two children case, we should replace the deleted node
        // by the rightmost element of the left subtree
        // or
        // by the leftmost element of the right subtree
        Node *temp;
        temp = root_node->left; // I choose the rightmost element of the left subtree
        while (temp->right != NULL) {
          temp = temp->right;
        }
        // copy the element to be repalced
        root_node->key = temp->key;
        root_node->left = deleteNode(root_node->left,temp->key);
      }
  }
  // If the tree has only one node
  if (root_node == NULL) {
    return root_node;
  }
  // Upadate the height of the root node
  root_node->height = (height(root_node) + 1);
  // Thus we verifies whether the current node is unbalanced or not and then rotate correctly to correct.
  if ((balanceFactor(root_node) > 1) && (root_node->key < root_node->left->key)) {
    //LeftLeft Case
    root_node = ll(root_node);
  }else if ((balanceFactor(root_node) > 1) && (root_node->key > root_node->left->key)) {
    //LeftRight Case
    root_node = lr(root_node);
  }else if ((balanceFactor(root_node) < -1) && (root_node->key > root_node->right->key)) {
    //RightRight Case
    root_node = rr(root_node);
  }else if ((balanceFactor(root_node) < -1) && (root_node->key < root_node->right->key)) {
      //Rightleft Case
      root_node = rl(root_node);
  }

  return root_node;
}
