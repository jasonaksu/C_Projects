#include "macros.h" //should always be before any use of LOG
#include "dlist.h"

/*
  Compile this program with following command.
  gcc dlist.c dlist_main.c logger.c -o dlist -lm
*/

#ifdef LOG
#include "logger.h"
extern log_t logger;  //the global variable logger from logger.h. "extern" means it is defined elsewhere. This makes the compiler happy, but the linker would need to find it.
#endif

#include "dlist_hidden.h"
#include <stdlib.h>
#include <stdio.h>


/*
  Initializes an empty doubly linked list, allocating memory for it
  and setting its head, tail, and length to initial values.
  Returns a pointer to the newly created list.
*/
list *init() {
  list *newlist = (list *)malloc(sizeof(list));
  newlist->head = NULL;
  newlist->tail = NULL;
  //length is 0
  newlist->length = 0;
  // Initialize the last accessed node and index
  newlist->last_accessed_node = NULL;
  // -1 indicates no node has been accessed yet.
  newlist->last_accessed_index = -1;
  return newlist;
}

// Frees all memory associated with the list, including its nodes.
void destroy(list *l) {
  node *curr = l->head;
  while (curr!=NULL) {
    node *next = curr->next;
    free(curr); // Free each node
    curr = next;
  }
  free(l); // Free the list structure itself.
}

/*
  void add_front function adds a new element to the front of the list.
  It handles both empty and non-empty lists. Updating the head and tail
  pointers as necessary, and incremets the lists length.
*/
void add_front(list* l, int element) {
  #ifdef LOG
  logger_add();
  #endif
  // Allocate memory for a new node and initialize it
  node *new_node = (node *)malloc(sizeof(node));
  new_node->element = element;
  
  // Link the new node to the current head of the list.
  new_node->next = l->head;
  
  // It is going to be the new head prev pointer becomes NULL
  new_node->prev = NULL;

  // If the list is not empty
  if (l->head != NULL) {
    l->head->prev = new_node;
  }
  // Update the head to the new node.
  l->head = new_node;

  // If the list was empty before adding set the tail to the new node as well
  if (l->tail == NULL) {
    l->tail = new_node;
  }
  // Increment the lists length
  l->length += 1;

  // Invaidate last accessed node data after adding an element.
  l->last_accessed_node = NULL;
  l->last_accessed_index = -1;
}

/*
  void add_back function adds a new element to the back of the list.
  Updates the tail of the list. Handles empty lists by setting
  the new node as both the head and the tail.
*/
void add_back(list *l,int element) {
  // Allocate memory for a new node
  node *new_node = (node *)malloc(sizeof(node));
  // Set the new nodes value
  new_node->element = element;
  // It is going to be last node so it's next pointer is NULL
  new_node->next = NULL;
  // Prev pointer of the new node points to the current last node.
  new_node->prev = l->tail;

  // If the list already has elements, link current to the new node.
  if (l->tail != NULL) {
    l->tail->next = new_node;
  } else {
    // If the list is empty, the new node becomes the head as well.
    l->head = new_node;
  }
  // Update the tail to the new node.
  l->tail = new_node;
  // Increment the length by 1
  l->length += 1;

  // Invalidate last accessed node after adding an element.
  l->last_accessed_node = NULL;
  l->last_accessed_index = -1;

  // Log the addition
  #ifdef LOG
  logger_add();
  #endif
}

/*
  Removes an element from the front of the list. It adjusts the head pointer
  and frees the removed node's memory, handling lists that become empty after removal.
*/
void remove_front(list* l) {
  // Check if the list is not empty.
  if (l->head != NULL) {
    // Store the current head in a temporary pointer for safe removal
    node *temp = l->head;
    // Move the head pointer to the next node
    l->head = l->head->next;

    // If the list still has elements set the new heads pre pointer to the null
    if (l->head != NULL) {
      l->head->prev = NULL;
    } else {
      // If the list is empty set tail to the null
      l->tail = NULL;
    }
    // Free the memory
    free(temp);
    // Decrement the length
    l->length -= 1;

    // Invalidate last accessed node after removal.
    l->last_accessed_node = NULL;
    l->last_accessed_index = -1;

    #ifdef LOG
    logger_add();
    #endif
  }
}

/*
  Removes an element from the back of the list. Adjusts the tail
  pointer and frees the removed node's memory, ensuring correct
  behavior for list that become empty.
*/
void remove_back(list* l) {
  // Check if the list is empty
  if (l->tail != NULL) {
    //The node to remove is the current tail
    node *temp = l->tail;
    // Update tail to the prev node
    l->tail = l->tail->prev;

    // If there is still elements set the new tails next pointer to null.
    if (l->tail != NULL) {
      l->tail->next = NULL;
    } else {
      // If the list is empty head should be NULL
      l->head = NULL;
    }
    
    // Free the memory of the removed node
    free(temp);
    // Decrement the length
    l->length -= 1;

    // Invalidate last accessed node after removal
    l->last_accessed_node = NULL;
    l->last_accessed_index = -1;

    #ifdef LOG
    logger_add();
    #endif
  }
}

/*
  int get funtion retrives the element at a specified index within the list.
  Includes optimizations for accessing elements based on the proximity
  to the last accessed node. Returns the element's value or -1 if the index
  is out of bounds.
*/  
int get(list *l,int index) {
  // Check if the requested index is out of the bound
  if ((index < 0) || (index >= l->length)) {
    return -1;
  }
  // Log the get operation
#ifdef LOG
  logger_add();
#endif
  
  // Initialization for traversal
  int i = 0;
  node *curr = NULL;
  
  // Optimize search using last accesed node if it provides closer start point.
  if (l->last_accessed_node != NULL && abs(l->last_accessed_index - index) < abs(l->length - index)) {
    // Set starting point to last accessed node and index.
    i = l->last_accessed_index;
    curr = l->last_accessed_node;
    
    // Determine search direction
    if (index > l->last_accessed_index) {
      // Move forward in the list until the desired index is reached
      while (i < index) {
	curr = curr->next;
	i++;
#ifdef LOG
	logger_add();
#endif
      }
    } else {
      // Move backward in list if the desired index is before the last accessed index
      while (i > index) {
	curr = curr->prev;
	i--;
#ifdef LOG
	logger_add();
#endif
      }
    }
  } else {
    // Start from head if last accessed node is not helpful.
    curr = l->head;
    while (i < index) {
      curr = curr->next;
      i++;
#ifdef LOG
      logger_add();
#endif
    }
  }

  // Update last accessed node and index.
  l->last_accessed_node = curr;
  l->last_accessed_index = index;

  // return the element at the requested index
  return curr->element;
}

/*
  Sets the value of an element at a specified index. It finds
  the correct node optimizing based on the last accessed node,
  and updates its value.
*/
void set(list* l,int index,int element) {
  // Check if the index is out of the bounds.
  if ((index < 0) || (index >= l->length)) {
    return; // Invalid index do nothing.
  }
#ifdef LOG
  logger_add();
#endif
  int i = 0;
  node *curr = NULL;

  // Optimize search using last accessed node.
  if (l->last_accessed_node != NULL && abs(l->last_accessed_index - index) < abs(l->length - index)) {

    // Start from the last accessed node
    i = l->last_accessed_index;
    curr =l->last_accessed_node;

    // Determine the direction for the search
    if (index > l->last_accessed_index) {
      // Move forward to find correct node.
      while (i < index) {
	curr = curr->next;
	i++;
#ifdef LOG
	logger_add();
#endif
      }
    } else {
      // Move backward to find correct node.
      while (i > index) {
	curr = curr->prev;
	i--;
#ifdef LOG
	logger_add();
#endif
      }
    }
  } else {
    // start from the head if no beneficial last accessed node or not set.
    curr = l->head;
    while (i < index) {
      curr = curr->next;
      i++;
#ifdef LOG
      logger_add();
#endif
    }
  }

  // Update the nodes element with the new value
  curr->element = element;

  // Update last accessed node and index
  l->last_accessed_node = curr;
  l->last_accessed_index = index;
}

int index_of(list* l,int element) {
  node *curr = l->head;
  int i=0;
#ifdef LOG
  logger_add();
#endif
  //find the first time the element is found
  while ((curr!=NULL) && (curr->element!=element)) {
    curr = curr->next;
    i+=1;
#ifdef LOG
    logger_add();
#endif
  }
  if (curr!=NULL) { //element is found
    return i;
  }
  return -1;
}

int length(list *l) {
  return l->length;
}

node *makenode(int element,node *next) {
  node *newnode = (node *)malloc(sizeof(node));
  newnode->element = element;
  newnode->next = next;
  return newnode;
}
