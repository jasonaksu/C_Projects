#ifndef __DLIST_H_
#define __DLIST_H_

#include <stdlib.h>

// Structure to represent a node of a doubly linked list
typedef struct d_node
{
  // Element stored in the node
  int element;
  // Pointer to the next node in the list
  struct d_node *next;
  // Added new pointer for previuous node
  struct d_node *prev; 
} node;

// Structure to represent the doubly linked list
typedef struct d_list
{
  // Pointer to the first node in the list.
  node *head;
  // Pointer to the last node in the list
  node *tail;
  // Number of nodes in the list.
  int length;
  // Last accessed node to optimize get/set operation
  node *last_accessed_node;
  // Index of the last accessed node
  int last_accessed_index;
} list;

//initialize and return an empty list
list *init();

//free all the memory of a list
void destroy(list *l);

//add the given element to the front of the given list
void add_front(list* l,int element);

//add the given element to the back of the given list
void add_back(list* l,int element);

//remove an element from the front of the given list
void remove_front(list* l);

//remove an element from the back of the given list
void remove_back(list* l);

//get the element at a specified index of the given list. If the index is invalid, it returns -1
int get(list* l,int index);

//set the element at the specified index of the given list. If the index is invalid, this function does nothing
void set(list* l,int index,int element);

//return the number of elements present in the given list
int length(list *l);

//return the index of the first occurrence of the given element in the given list. If the element is not present, this function returns -1
int index_of(list* l,int element);

#endif
