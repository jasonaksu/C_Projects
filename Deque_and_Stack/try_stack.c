#include "stack.h"
#include <stdio.h>

//To compile this program after completing the deque implementation, type:

//gcc try_stack.c stack.c deque.c -o stack

//then run with ./stack

int main() {
  stack_t stack;
  int i;
  unsigned int s;

  
  make_empty_stack(&stack);

  for (i=1;i<=10;i+=1) {
    push(&stack,i);
    printf("Pushed %d\n",i);
  }

  s = stack_size(&stack);
  printf("After pushing 10 elements, size is %u\n",s);

  for (i=0;i<5;i+=1) {
    int data = top(&stack);
    pop(&stack);
    printf("Popped: %d\n",data);
  }

  s = stack_size(&stack);

  printf("After popping 5 elements, size is %u\n",s);

  for (i=1;i<=5;i+=1) {
    push(&stack,10+i);
    printf("Pushed %d\n",10+i);
  }

  while (!empty_stack(&stack)) {
    int data = top(&stack);
    pop(&stack);
    printf("Popped %d\n",data);
  }
}
