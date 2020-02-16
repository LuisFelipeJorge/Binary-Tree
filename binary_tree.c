#include <stdio.h> //Standard header for C language.
#include <stdlib.h>// Contains functions as malloc, that help to dynamically allocate the memory.
#include <stdbool.h> // Allow us to work with boolean type
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
};

//Definition of the functions that will be used in the program
///////////////////////////////////////////////////////

struct Node* createNode(int new_key); // Function to allocate extra memory for a new node.
struct Node* insert(struct Node* root_node,int new_key); // Function to insert a new element in the tree.
bool search(struct Node* root_node,int key);// Function to check whether an element is present in the tree or not.
void cleanTree(struct Node* root_node);// Function to free the memory allocated for the tree

///////////////////////////////////////////////////////

int main(int argc, char const *argv[]) {
  struct Node* root = NULL;
  root = insert(root,25);
  root = insert(root,15);
  root = insert(root,30);
  root = insert(root,12);
  root = insert(root,20);
  root = insert(root,27);
  root = insert(root,33);
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

  cleanTree(root);

  return 0;
}

///////////////////////////////////////////////////////

struct Node* createNode(int new_key){
  struct Node* temp = (struct Node*)malloc(sizeof(struct Node)); // temporary variable to help to allocate the memory
  temp->key = new_key;      // Store the data
  temp->right = temp->left = NULL; // new node do not have childs at first moment
  return temp; // return the new node
}

///////////////////////////////////////////////////////
/*
Binary trees are recursive structures, so we will generally choose this approach
to solve problems in our functions
*/
struct Node* insert(struct Node* root_node,int new_key){

  if (root_node == NULL) {
    // In the case that the tree is empty:
    root_node = createNode(new_key);
  }else if (new_key <= root_node->key) {
    // In this case, the value of the new element is less than the value at the root.
    // Therefore, we must place them in the left subtree.
    root_node->left = insert(root_node->left,new_key);
  }else{
    // In this case, the value of the new element is greater than the value at the root.
    // Therefore, we must place them in the right subtree.
    root_node->right = insert(root_node->right,new_key);
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

void cleanTree(struct Node* root_node){
  if (root_node == NULL) { // Empty tree
    return; // Do nothing
  }else{
    // Delete the subtrees
    cleanTree(root_node->left);
    cleanTree(root_node->right);
    free(root_node);
  }
}

///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
