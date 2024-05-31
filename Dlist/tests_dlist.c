/*
  Compile this file with following command
  gcc -o test_dlist tests_dlist.c dlist.c logger.c
*/

#include "dlist.h"
#include <stdio.h>
#include <stdlib.h>

int tests_run = 0;
int tests_passed = 0;
int tests_failed = 0;

void test_init() {
  printf("---Test init begin:---\n");
  list* mylist = init(); // Initialize the list and store the reference in mylist.

  // Check if the list initialized correctly.
  if (mylist != NULL && mylist->head == NULL && mylist->tail == NULL && mylist->length == 0) {
    printf("PASS: List initialized correctly.\n");
    tests_passed++; // Increment tests passed.
  } else {
    printf("Test failed.\n");
    tests_failed++; // If test failed increment tests failed.
  }
  tests_run++; // increment tests run
  destroy(mylist); // Destroy the list to free allocated memory
  printf("-- Test test_init end:---\n");
}

void test_add_front() {
  printf("---Test test_add_front begin:---\n");
  list* mylist = init(); // Initialize the list

  // Add elements to the front of the list in reverse order.
  add_front(mylist, 1);
  add_front(mylist, 9);
  add_front(mylist, 0);
  add_front(mylist, 3);

  // Check if the first element is 3. (most recent added element.)
  if (mylist->head->element == 3 && mylist->length == 4) { // Check if the list length 4.
    printf("PASS: Elements added correctly at the front.\n");
    tests_passed++; // If passed increment tests passed
  } else {
    printf("Test failed.\n");
    tests_failed++; // increment tests failed if failed
  }
  tests_run++; // increment tests run
  destroy(mylist); // Free allocated memory
  printf("Test test_add_front end:---\n");
}

void test_add_back() {
  printf("---Test test_add_back begin:---\n");
  list* mylist = init(); // Initialize

  // Add elements to the back of the list
  add_back(mylist, 5);
  add_back(mylist, 10);

  // Check if the last element is 10 and list consist of 2 elements in total.
  if (mylist->tail->element == 10 && mylist->length == 2) {
    printf("PASS: Elements added correctly at the back. \n");
    tests_passed++; // Increment if passed
  } else {
    printf("Test failed.\n");
    tests_failed++; // Increment if failed
  }
  tests_run++; // Increment tests run
  destroy(mylist); // free
  printf("---Test test_add_back end:---\n");
}

void test_remove_front() {
  printf("---Test test_remove_front begin:---\n");
  list*mylist = init();
  add_front(mylist, 2); // add element
  add_front(mylist, 8); // add element
  remove_front(mylist); // Remove the front element from the list which is 8

  // Check if the new front element is 2 and the length of the list is 1
  if (mylist->head->element == 2 && mylist->length == 1) {
    printf("PASS: Element removed correctly from the front.\n");
    tests_passed++;
  } else {
    printf("Test failed.\n");
    tests_failed++;
  }
  tests_run++;
  destroy(mylist);
  printf("---Test test_remove_front end:---\n");
}

void test_remove_back() {
  printf("---Test test_remove_back begin:---\n");
  list* mylist = init(); // initialize a new list
  add_back(mylist, 3); // add element to the back
  add_back(mylist, 7); // add element to the back
  remove_back(mylist); // remove element from the back of the list which is 7

  // Check if the new tail is 3 and the length is 1
  if (mylist->tail->element == 3 && mylist->length == 1) {
    printf("PASS: Element removed correctly from the back.\n");
    tests_passed++;
  } else {
    printf("Test failed.\n");
    tests_failed++;
  }
  tests_run++;
  destroy(mylist);
  printf("---Test test_remove_back end:---\n");
}

void test_get() {
  printf("---Test test_get begin:---\n");
  list* mylist = init(); // initialize a new list.

  // Test getting from an empty list
  if (get(mylist, 0) == -1) {
    printf("PASS: Test get from an empty list\n");
    tests_passed++;
  } else {
    printf("Test failed.\n");
    tests_failed++;
  }
  tests_run++;

  // Setup for further tests
  add_back(mylist, 1); // Add element to back [1]
  add_back(mylist, 9); // Add element to back [1, 9]
  add_back(mylist, 0); // List [1, 9, 0]
  add_back(mylist, 3); // List [1, 9, 0, 3]

  // Test getting the first element
  if (get(mylist, 0) == 1) {
    printf("PASS: Test get first element\n");
    tests_passed++;
  } else {
    printf("Test failed.\n");
    tests_failed++;
  }
  tests_run++;

  // Test getting a middle element
  if (get(mylist, 1) == 9) {
    printf("PASS: Test get middle element\n");
    tests_passed++;
  } else {
    printf("Test failed.\n");
    tests_failed++;
  }
  tests_run++;

  // Test getting the last element
  if (get(mylist, 3) == 3) {
    printf("PASS: Test get last element\n");
    tests_passed++;
  } else {
    printf("Test failed.\n");
    tests_failed++;
  }
  tests_run++;

  // Test getting with an invalid index (out of bounds)
  if (get(mylist, 4) == -1) {
    printf("PASS: Test get with invalid index\n");
    tests_passed++;
  } else {
    printf("FAIL: Test get with invalid index\n");
    tests_failed++;
  }
  tests_run++;

  // Cleanup
  destroy(mylist);
  printf("---Test test_get end---\n");
}

void test_set() {
  printf("---Test test_set begin:---\n");
  list* mylist = init();
  
  // Test setting in a non-empty list
  add_back(mylist, 1); // List now: [1]
  add_back(mylist, 2); // List now: [1, 2]
  set(mylist, 1, 3);   // Should set the second element to 3. List should be [1, 3]
  if (get(mylist, 1) == 3) {
    printf("PASS: Test set in non-empty list\n");
    tests_passed++;
  } else {
    printf("Test failed.\n");
    tests_failed++;
  }
  tests_run++;

  // Test setting at the beginning of the list
  set(mylist, 0, 4);   // Should set the first element to 4. List should be [4, 3]
  if (get(mylist, 0) == 4) {
    printf("PASS: Test set at the beginning of the list\n");
    tests_passed++;
  } else {
    printf("Test failed.\n");
    tests_failed++;
  }
  tests_run++;

  // Test setting at the end of the list
  add_back(mylist, 5); // List now [4, 3, 5]
  set(mylist, 2, 6);   // Should set the last element to 6. List should be [4, 3, 6]
  if (get(mylist, 2) == 6) {
    printf("PASS: Test set at the end of the list\n");
    tests_passed++;
  } else {
    printf("Test failed.\n");
    tests_failed++;
  }
  tests_run++;

  // Test setting with invalid index
  set(mylist, 3, 7);   // Out of bounds, should do nothing.
  if (length(mylist) == 3) {
    printf("PASS: Test set with invalid index (no change)\n");
    tests_passed++;
  } else {
    printf("Test failed (unexpected change)\n");
    tests_failed++;
  }
  tests_run++;

  // Cleanup
  destroy(mylist);
  printf("---Test set end---\n");
}

void test_index_of() {
  printf("---Test test_index_of begin:---\n");
  list* mylist = init(); // Initialize a new list
  // Add elements to the back of the list
  add_back(mylist, 6);
  add_back(mylist, 7);
  add_back(mylist, 8);

  // Find the index of the element 7
  int index = index_of(mylist, 7);
  if (index == 1) {
    printf("PASS: Correct index found for element.\n");
    tests_passed++; // If correct increment
  } else {
    printf("Test failed.\n");
    tests_failed++;
  }
  tests_run++;
  
  // Search for an element not in the list
  index = index_of(mylist, 10);

  // Check if searching for a non existed element returns -1
  if (index == -1) {
    printf("PASS: Correct handling of searching for non-existing element.\n");
    tests_passed++;
  } else {
    printf("FAIL: Incorrect handling of searching for non-existing element.\n");
    tests_failed++;
  }
  tests_run++;
  destroy(mylist);
  printf("---Test test_index_of end:---\n");
}

int main() {

  test_init();
  test_add_front();
  test_add_back();
  test_remove_front();
  test_remove_back();
  test_get();
  test_set();
  test_index_of();

  printf("Ran %d tests, passed %d tests, failed %d tests\n", tests_run, tests_passed, tests_failed);
  return 0;
}
