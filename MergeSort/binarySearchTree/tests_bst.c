#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int tests_run = 0;
int tests_passed = 0;
int tests_failed = 0;

void test_size() {
  printf("---Test size begin:---\n");
  // Creating a test tree.
  bst_node_t* root = NULL;
  root = add(root, 1);
  add(root, 9);
  add(root, 0);
  add(root, 3);

  int expected_size = 4;
  int actual_size = size(root);
  tests_run++;
  if (actual_size == expected_size) {
    tests_passed++;
    printf("PASSED\n");
  } else {
    tests_failed++;
    printf("FAILED\n");
  }
  clean(root);
  printf("---Test size end:---\n");
}

void test_exists() {
  printf("---Test exists begin:---\n");
    // Creating a test tree.
  bst_node_t* root = NULL;
  root = add(root, 1);
  add(root, 9);
  add(root, 0);
  add(root, 3);

  tests_run++;
  if (exists(root, 0) && !exists(root, 77)) {
    tests_passed++;
    printf("PASSED\n");
  } else {
    tests_failed++;
    printf("FAILED\n");
  }
  clean(root);
  printf("---Test exists end:---\n");
}

void test_height() {
  printf("---Test height begin:---\n");
  // Creating a test tree.
  bst_node_t* root = NULL;
  root = add(root, 1);
  add(root, 9);
  add(root, 0);
  add(root, 3);

  int expected_height = 2;
  int actual_height = height(root);
  tests_run++;

  if (actual_height == expected_height) {
    tests_passed++;
    printf("PASSED\n");
  } else {
    tests_failed++;
    printf("FAILED\n");
  }
  clean(root);
  printf("---Test height end:---\n");
}

void test_is_balanced() {
  printf("---Test is_balanced begin:---\n");
    // Creating a test tree.
  bst_node_t* root = NULL;
  root = add(root, 1);
  add(root, 9);
  add(root, 0);
  add(root, 3);

  tests_run++;
  if (is_balanced(root)) {
    tests_passed++;
    printf("PASSED\n");
  } else {
    tests_failed++;
    printf("FAILED\n");
  }
  clean(root);
  printf("---Test is_balanced end:---\n");
}

int main() {
  test_size();
  test_exists();
  test_height();
  test_is_balanced();

  printf("Ran %d tests, passed %d tests, failed %d tests\n", tests_run, tests_passed, tests_failed);
  return 0;
}
