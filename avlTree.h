// Headers files 
#include <stdio.h> //Standard header for C language.
#include <stdlib.h>// Contains functions as malloc, that help to dynamically allocate the memory.
#include <stdbool.h> // Allow us to work with boolean type
#include <limits.h> // contains the INT_MIN value.

//Definition of the data structure
///////////////////////////////////////////////////////
typedef struct Node{
  /*
  A binary tree is made up of nodes that carry three pieces of information.
  Data and 2 pointers for other nodes.
  We could see the nodes as cells with sub-divisions
         ******************       The middle cell stores the data that we want to save
    <----*ptr | Data | ptr*---->  the others cells stores the pointers that represent the links
         ******************       other nodes.
  */
  int key;                  //represents the data we want to store, in this case, it's an integer.
  struct Node *left,*right; // pointes that link to other nodes .
  int height;// Stores the node height value, it will help in the process of balancing the tree.
}Node;

///////////////////////////////////////////////////////
//Functions to create the  structure
///////////////////////////////////////////////////////

Node* createNode(int);          // Function to allocate extra memory for a new node.
Node* insert(Node*, int);       // Function to insert a new element in the tree.
Node* deleteNode(Node*, int);   // Function to remove an element from the tree.
bool search(Node*, int);        // Function to check whether an element is present in the tree or not.
void cleanTree(Node**);         // Function to free the memory allocated for the tree.
int findMinimum(Node*);         // Find the minimum value in the binary search tree.
int findMaximum(Node*);         // Find the maximum value in the binary search tree.
int getmax(int , int);          // Utility function to obtain the maximum value between two numbers.
int height(Node*);              // Function to find the height of a node.

///////////////////////////////////////////////////////
//Functions to balance the tree
///////////////////////////////////////////////////////

Node* rotateRight(Node*);       // Function to execute right rotation.
Node* rotateLeft(Node*);        // Function to execute left rotation.
Node* rr(Node*);                // Function to execute double right rotation.
Node* ll(Node*);                // Function to execute double left rotation.
Node* rl(Node*);                // Function to execute double right left rotation.
Node* lr(Node*);                // Function to execute double left right rotation.
int balanceFactor(Node*);       // Funtion to get the balance factor of a node.

///////////////////////////////////////////////////////
//Functions to print the tree
///////////////////////////////////////////////////////

void preorder(Node*);           // (Root, Left, Right)
void inorder(Node*);            // (Left, Root, Right) 
void postorder(Node*);          // (Left, Right, Root)


