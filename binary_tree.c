#include <stdio.h> //Standard header for C language.
#include <stdlib.h>// Contains functions as malloc, that help to dynamically allocate the memory.
#include <stdbool.h> // Allow us to work with boolean type
//#include <limits.h> // contains the INT_MIN value.
#include "bst_avl.h"

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

  root = insert(root, 11); // creating an imbalance
  root = insert(root,9);
  root = insert(root,60);
  root = insert(root,45);
  root = insert(root,29);
  root = insert(root,28);
  root = insert(root,16);
  root = insert(root,18);

  // testing the print functions
  preorder(root);
  printf("\n");
  inorder(root);
  printf("\n");
  postorder(root);
  printf("\n");

  int min = findMinimum(root);
  printf("Minimun value : %d \n",min);
  int max = findMaximum(root);
  printf("Maximum value : %d \n",max);

  //testing the delete function
  printf("\n");
  root = delete(root,25);
  preorder(root);
  printf("\n");
  inorder(root);
  printf("\n");
  postorder(root);
  printf("\n");

  printf("\n");
  root = delete(root,30);
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

