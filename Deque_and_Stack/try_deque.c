#include "deque.h"
#include <stdio.h>

//To run this after completing the deque implementation,
//type: gcc try_deque.c deque.c -o deque

//then run with ./deque

int main() {
  deque_t deque;
  int i;
  unsigned int s;

  
  make_empty_deque(&deque);

  for (i=5;i<=10;i+=1) {
    add_back(&deque,i);
    printf("Added %d to back of queue.\n",i);
  }

  s = deque_size(&deque);
  printf("After adding 6 elements, size of deque is %u\n",s);

  for (i=4;i>0;i-=1) {
    add_front(&deque,i);
    printf("Added %d to front of queue.\n",i);
  }

  s = deque_size(&deque);

  printf("After adding 4 elements, size is %u\n",s);

  for (i=0;i<s/2;i+=1) {
    int data = get_front(&deque);
    remove_front(&deque);
    printf("Removed %d from front.\n",data);
  }

  for (i=0;i<s/2;i+=1) {
    int data = get_back(&deque);
    remove_back(&deque);
    printf("Removed %d from back.\n",data);
  }

  delete_deque(&deque);
}
