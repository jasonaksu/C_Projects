#ifndef __STACK_H__
#define __STACK_H__

#include "deque.h"
#include "stdbool.h"

/*

  This header file contains the representation and operations on a stack.

  A stack is a list-like data structure. Like a real-world stack, one can add
  and remove elements from it. The last element added to the stack is the first element
  to be removed. This is called a Last-In-First-Out behavior, or LIFO.

  Adding to a stack is called "pushing", and removing from a stack is called "popping".
  The element last added to the stack is called the "top". 
  Imagine a vertical stack of dinner plates to better understand why these operations are named so!

  Because a stack is basically a list, it is implemented using a list. In this case,
  we implement the stack using a deque.

  This means that each operation of the stack is implemented by using one or more
  operations on a deque.

*/  

//reuse the deque representation for our stack
typedef deque_t stack_t;

//make an empty stack
void make_empty_stack(stack_t *st);

//delete the given stack
void delete_stack(stack_t *st);

//push an element onto the given stack
void push(stack_t *st,int data);

//return the element on "top" of the stack. This is the element last added.
//the stack is not changed as a result of this operation.
int top(stack_t *st);

//Pop from the top of the given stack (i.e. removed the element that was last added).
void pop(stack_t *st);

//get the size of the given stack.
unsigned int stack_size(stack_t *st);

//is this stack empty?
bool empty_stack(stack_t *st);

#endif
