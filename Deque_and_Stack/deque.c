#include "deque.h"
#include <stdlib.h>

// Make an empty deque
void make_empty_deque(deque_t *dq) {
  dq->head = make_node(0, NULL); //Dummy node.
  dq->tail = dq->head; // Tail points to the Dummy node.
}

// Delete an existing deque and free all nodes.
void delete_deque(deque_t *dq) {
  // Initialize current node as the head of the deque.
  deque_node_t *current = dq->head;
  // Loop until reaching the end of the deque
  while (current != NULL) {
    // Hold the current to free it after moving the next node.
    deque_node_t *temp =current;
    // Move to the next one.
    current = current->next;
    // Free the memory.
    free(temp);
  }
  dq->head = dq->tail = NULL; // Reset head and tail to NULL.
}

// Add the given data to the front of the given deque
void add_front(deque_t *dq,int data) {
  // Create a new node after the dummy node
  deque_node_t *new_node = make_node(data, dq->head->next);
  // Insert the new node after the dummy
  dq->head->next = new_node;
  // If the deque was empty
  if (dq->tail == dq->head) {
    // Update tail to the new node.
    dq->tail = new_node;
  }
}

// Add the given data to the back of the given deque
void  add_back(deque_t *dq, int data) {
  // Create a new node.
  deque_node_t *new_node = make_node(data, NULL);
  // Link the new node at the end of the deque.
  dq->tail->next = new_node;
  // Update the tail to the new node.
  dq->tail = new_node;
}

// Get the element at the front of the deque. If the deque is empty, return -12345.
int get_front(deque_t *dq) {
  // Check if the deque is empty
  if (dq->head->next == NULL) {
    return -12345;
  }
  //Return the data of the first node.
  return dq->head->next->data;
}

// Get the element at the back of the deque. If the deque is empty return -12345
int get_back(deque_t *dq) {
  // Check if the deque is empty.
  if (dq->tail == dq->head) {
    return -12345;
  }
  // Return the data of the last node.
  return dq->tail->data;
}

// Remove the element at the front of the queue
void remove_front(deque_t *dq) {
  // Check if its empty.
  if (dq->head->next == NULL) {
    return; //Nothing
  }
  // Not to be removed
  deque_node_t *temp = dq->head->next;
  // Bypass the node being removed.
  dq->head->next = temp->next;
  // If removing the last element.
  if (dq->tail == temp) {
    // Tail to dummy node.
    dq->tail = dq->head;
  }
  // Free the node.
  free(temp);
}

// Remove the element at the back of the queue.
void remove_back(deque_t *dq) {
  // Check if its empty.
  if (dq->tail == dq->head) {
    return; // Nothing
  }

  //Move from the dummy node to node before the last one.
  deque_node_t *current = dq->head;
  while (current ->next != dq->tail) {
    current = current->next;
  }
  // Now Current points to the node before the last node.

  // Free the last node.
  free(dq->tail);
  // Update the next node
  current->next = NULL;
  // Update the tail pointer.
  dq->tail = current;
}

// Return the size (number of things) in the given deque.
unsigned int deque_size(deque_t *dq) {
  unsigned int size = 0;
  // Start counting from the first node.
  deque_node_t *current = dq->head->next;
  while (current != NULL) {
    size++;
    current = current->next;
  }return size;
}

// Helper function to create a new node for deque
deque_node_t *make_node(int data,deque_node_t *next) {
  // Allocate memory for new node.
  deque_node_t *node = (deque_node_t *)malloc(sizeof(deque_node_t));
  // If memory allocation is successful, initialize node.
  if (node) {
    // Set nodes data.
    node->data =data;
    //set nodes next pointer.
    node->next = next;
  }
  //Return the new node.
  return node;
}
