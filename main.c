#include "avlTree.h"

int main(int argc, char const *argv[]){
  
  Node* root = NULL;
  ////////////////////////////////
  // Testing height
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

  ////////////////////////////////
  // Testing search()
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

  ////////////////////////////////
  // Testing imbalance
  root = insert(root, 11); // Creating an imbalance
  root = insert(root,9);
  root = insert(root,60);
  root = insert(root,45);
  root = insert(root,29);
  root = insert(root,28);
  root = insert(root,16);
  root = insert(root,18);

  ////////////////////////////////
  // Testing print functions
  preorder(root);
  printf("\n");
  inorder(root);
  printf("\n");
  postorder(root);
  printf("\n");

  ////////////////////////////////
  // Testing the functions to find maximum and minimum values 
  int min = findMinimum(root);
  printf("Minimun value : %d \n",min);
  int max = findMaximum(root);
  printf("Maximum value : %d \n",max);

  ////////////////////////////////
  // Testing the delete function
  printf("\n");
  root = deleteNode(root,25);
  preorder(root);
  printf("\n");
  inorder(root);
  printf("\n");
  postorder(root);
  printf("\n");

  printf("\n");
  root = deleteNode(root,30);
  preorder(root);
  printf("\n");
  inorder(root);
  printf("\n");
  postorder(root);
  printf("\n");

  ////////////////////////////////
  // Free the memory allocated
  cleanTree(&root);
  min = findMinimum(root);
  printf("Minimun value : %d \n",min);
  max = findMaximum(root);
  printf("Maximum value : %d \n",max);
  
  return 0;
}
