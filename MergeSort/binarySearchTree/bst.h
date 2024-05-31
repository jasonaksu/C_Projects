#ifndef __BST_H__
#define __BST_H__

#include <stdbool.h>

typedef struct bst_node {
  int data;
  struct bst_node* left;
  struct bst_node* right;
} bst_node_t;

int size(bst_node_t *root);

//add the specified element to the BST and return the root
//of the resulting BST
bst_node_t* add(bst_node_t *root,int element);

//find if the specified element exists in the given BST
bool exists(bst_node_t* root,int element);

//find if the given BST is balanced. a BST is balanced if
//all its nodes are balanced. A node is balanced if the number
//of nodes in its left and right subtrees differ by at most one.
//an empty tree is trivially balanced.
bool is_balanced(bst_node_t *root);

//find the height of the given BST. The height of a BST is the
//number of edges in the longest path from the root to a leaf.
//the height of an empty tree is -1
int height(bst_node_t *root);

//free the memory occupied by the given BST
void clean(bst_node_t* root);



#endif
