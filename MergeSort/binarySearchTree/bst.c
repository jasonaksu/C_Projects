#include "bst.h"
#include <stdlib.h>

bst_node_t *makenode(int element,bst_node_t *left,bst_node_t *right) {
  bst_node_t *root;
  root = (bst_node_t *)malloc(sizeof(bst_node_t));
  root->data = element;
  root->left = left;
  root->right = right;
  return root;
}

/*
  Recursively count the number of nodes in the
  left and right subtrees and add one for the
  current node to calculate the size of the BST.
*/
int size(bst_node_t * root) {
  // Base case: If the current node is NULL, the size is 0.
  if (root == NULL) {
    return 0;
  }
  // Recursively calculate the size of the left subtree,
  // add 1 for the current node, and then add the size of the right subtree.
  return size(root->left) + 1 + size(root->right);
}

bst_node_t *add (bst_node_t *root,int element) {
 
  bst_node_t *curr = root;
  bst_node_t *prev = NULL;
  
  while ((curr!=NULL) && (curr->data!=element)) {
    prev = curr;
    if (curr->data>element) {
      curr = curr->left;
    }
    else {
      curr = curr->right;
    }
  }
  
  if (curr==NULL) {
    curr = makenode(element,NULL,NULL);
    if (prev!=NULL) {
      if (prev->data>element) {
      	prev->left = curr;
      }
      else {
	      prev->right = curr;
      }
    }
    else {
      root = curr;
    }
  }
  return root;
}

/*
  To find a specific element in a Binary Search Tree (BST), we need to traverse the tree.
  If the element we are looking for matches the current node's data, return true.
  If not, continue search by moving to the left or right subtree based on
  whether the element is less than or greater than the current node's data.
*/
bool exists(bst_node_t *root,int element) {
  // Base case: element not found.
  if (root == NULL) return false;
  // Element found.
  if (root->data == element) return true;
  // Recursive search in left or right subtree.
  return element < root->data ? exists(root->left, element) : exists(root->right, element);
}

/*
  To calculate the height of a BST, we can recursively find the
  height of the left and right subtrees. The height of a tree is
  determined by taking the maximum of the heights of its
  left and right subtrees and adding one. If the tree is empty,
  the function should return -1.
*/
int height(bst_node_t *root) {
  // Base case: height of an empty tree is -1.
  if (root == NULL) return -1;
  int leftHeight = height(root->left);
  int rightHeight = height(root->right);
  // Return the greater height + 1
  return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

/*
  A binary search tree (BST) is considered balanced when
  the difference in height between the left and right subtrees is at most one.
  int height(bst_node_t *root) function is used to calculate heights and
  recursively check the balance of each node. If any subtree is unbalanced,
  false is returned.
*/
bool is_balanced(bst_node_t *root) {
  // Base case: Anempty tree is balanced.
  if (root == NULL) {
    return true;
  }

  // Calculate the size of the subtrees.
  int leftSize = size(root->left);
  int rightSize = size(root->right);

  // Check if the current node is balanced and recurse for left and right children.
  // Current node is balanced if height difference <= 1
  if (abs(leftSize - rightSize) <= 1
      // Left and right subtree is balanced
      && is_balanced(root->left) && is_balanced(root->right)) {
    // The tree is balanced.
    return true;
  } else {
    // The tree is not balanced.
    return false;
  }
}

/*
  Traverse the tree in post-order to free child nodes
  before their parent, thus avoiding accessing memory
  that has already been freed.
*/  
void clean(bst_node_t *root) {
  if (root != NULL) {
    // Recursively free left subtree.
    clean(root->left);
    // Free right subtree.
    clean(root->right);
    // Free the current node.
    free(root);
  }
}
      
