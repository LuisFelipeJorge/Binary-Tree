
//Functions to create the  structure
///////////////////////////////////////////////////////

struct Node* createNode(int new_key); // Function to allocate extra memory for a new node.
struct Node* insert(struct Node* root_node,int new_key); // Function to insert a new element in the tree.
struct Node* delete(struct Node* root_node,int key);// Function to remove an element from the tree.
bool search(struct Node* root_node,int key);// Function to check whether an element is present in the tree or not.
void cleanTree(struct Node** root_node);// Function to free the memory allocated for the tree.
int findMinimum(struct Node* root_node); // Find the minimum value in the binary search tree.
int findMaximum(struct Node* root_node);// Find the maximum value in the binary search tree.
int getmax(int a, int b);  // Utility function to obtain the maximum value between two numbers.
int height(struct Node* root_node); // Function to find the height of a node.

//Functions to balance the tree

struct Node* rotateRight(struct Node* x); // Function to execute right rotation.
struct Node* rotateLeft(struct Node* y); // Function to execute left rotation.
struct Node* rr(struct Node* root_node);// Function to execute double right rotation.
struct Node* ll(struct Node* root_node);// Function to execute double left rotation.
struct Node* rl(struct Node* root_node);// Function to execute double right left rotation.
struct Node* lr(struct Node* root_node);// Function to execute double left right rotation.
int balanceFactor(struct Node* root_node); // Funtion to get the balance factor of a node.

//Functions to print the tree
void preorder(struct Node* root_node);
void inorder(struct Node* root_node);
void postorder(struct Node* root_node);

///////////////////////////////////////////////////////
