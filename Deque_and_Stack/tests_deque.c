#include <stdio.h>
#include "deque.h"

/*
  Compile this file with following command.
  gcc tests_deque.c deque.c -o tests_deque
*/


// Test for adding and removing elements from both ends.
int test_add_and_remove() {
  printf("---Test test_add_and_remove begin:---\n");
  deque_t dq;
  make_empty_deque(&dq);
  // Adding elements.
  add_front(&dq, 1); // Deque is 1
  add_back(&dq, 2); // Deque is 1, 2
  add_front(&dq, 0); // Deque is 0, 1, 2
  add_back(&dq, 3); // Deque is  0, 1, 2, 3

  //check size
  if (deque_size(&dq) != 4) {
    printf("Test failed. Expected size 4 but got %u\n", deque_size(&dq));
    return 0;
  }

  // Removing elements.
  remove_front(&dq); // Deque is 1, 2, 3
  remove_back(&dq); // Deque is 1, 2

  // Check if elements are correct after removals.
  if (get_front(&dq) != 1 || get_back(&dq) != 2) {
    printf("Unexpected elements removal. Expected font 1, back 2 but got front %d, back%d\n", get_front(&dq), get_back(&dq));
    return 0;
  }

  printf("---Test test_add_and_remove end:---\n");
  return 1;
}

// Test empty deque
int test_empty_deque() {
  printf("---Test test_empty_deque begin:---\n");
  deque_t dq;
  make_empty_deque(&dq);

  // When attempting to remove from empty deque it should not crash.
  remove_front(&dq);
  remove_back(&dq);

  // Check the size if it is remaining 0
  if (deque_size(&dq) != 0) {
    printf("Deque is not empty size is %u\n", deque_size(&dq));
    return 0;
  }

  printf("---Test test_empty_deque end:---\n");
  return 1;
}

// Main function to run test cases and provide summary.
int main() {
  int total_tests = 2;
  int tests_passed = 0;

  tests_passed += test_add_and_remove();
  tests_passed += test_empty_deque();

  printf("Ran %d tests, passed %d tests, failed %d tests\n", total_tests, tests_passed, total_tests - tests_passed);

  return 0;
}
