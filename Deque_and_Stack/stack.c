#include "stack.h"

void make_empty_stack(stack_t *st) {
  make_empty_deque(st);
}

void push(stack_t *st,int data) {
  add_back(st,data);
}

void pop(stack_t *st) {
  remove_back(st);
}

int top(stack_t *st) {
  return get_back(st);
}

unsigned int stack_size(stack_t *st) {
  return deque_size(st);
}

bool empty_stack(stack_t *st) {
  return (stack_size(st)==0);
}
