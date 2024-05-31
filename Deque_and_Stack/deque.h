#ifndef __DEQUE_H__
#define __DEQUE_H__

/*

  This header file contains the representation and functions of a doubly-ended queue.

  A double-ended queue is called a deque, pronounced "deck".
  
  A deque is a list that supports adding and removing elements from
  either end.

 */

//a single node of the deque
typedef struct deque_node {
  int data;
  struct deque_node *next;
} deque_node_t;

//the deque itself
typedef struct deque {
  deque_node_t *head;
  deque_node_t *tail;
} deque_t;

//Make an empty deque
void make_empty_deque(deque_t *dq);

//delete an existing deque
void delete_deque(deque_t *dq);

//add the given data to the front of the given deque
void add_front(deque_t *dq,int data);

//add the given data to the back of the given deque
void add_back(deque_t *dq,int data);

//get the element at the front of the deque. If the deque is empty, return -12345
int get_front(deque_t *dq);

//get the element at the back of the queue. If the deque is empty, return -12345
int get_back(deque_t *dq);

//remove the element at the front of the queue
void remove_front(deque_t *dq);

//remove the element at the back of the queue
void remove_back(deque_t *dq);

//return the size (number of things) in the given deque
unsigned int deque_size(deque_t *dq);

//helper function to create a new node for the deque
deque_node_t *make_node(int data,deque_node_t *next);

#endif
