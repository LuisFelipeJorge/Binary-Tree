# Binary Search Tree
In computer science, a tree is a non-linear data structure in which we can express hierarchical relationships. The elements of a tree are called **nodes**, the first element is the **root node**, the root node can be linked to other nodes, we call the linked nodes as children of the root. In a generic tree, each node has an undefined number of children, but in a binary tree, nodes can have a maximum of two children, the left child and the right child. The nodes may store some data, called the **key value**, it could be an integer, a float a char or a data of another type.

![Binary Tree example](/home/luis/Documentos/ICC-2/Binary_Tree/binaryTree.png "Binary Tree")

To make it as a **Binary Search Tree** it is necessary to implement a methodology to insert new elements inside the structure. It is chosen to place the nodes according to the values ​​stored in them, if a child has a key value that is greater than the value of its parent, this node must be placed as the right child, otherwise, as the left child.  Doing this way, it is possible to implement the binary search algorithm.


