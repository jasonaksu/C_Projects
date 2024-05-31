#include "quicksort.h"
#include <stdio.h>
#include <stdbool.h>

int tests_run = 0;
int tests_passed = 0;
int tests_failed = 0;

void print_array( int *A, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", A[i]);
  }
  printf("\n");
}

// Function to check if an array is in non descending order.
bool is_sorted( int *A, int size) {
  for (int i = 1; i < size; i++) {
    if (A[i - 1] > A[i]) {
      return false;
    }
  }
  return true;
}

// Function to run a test case.
void run_test(int *A, int size, char *test_name) {
  tests_run++;
  printf("Testing: %s\n", test_name);
  quicksort(A, size);
  if (is_sorted(A, size)) {
    tests_passed++;
    printf("PASSED\n");
  } else {
    tests_failed++;
    printf("FAILED\n");
  }
  print_array(A, size);
  printf("\n");
}

void test_small_arrays() {
  printf("---Test small_arrays begin:---\n");
  int A[] = {10, 7, 8, 9, 1, 5};
  int n = sizeof(A) / sizeof(A[0]);
  run_test(A, n, "Small Array");
  printf("---Test small_arrays end:---\n\n");
}

void test_sorted_arrays() {
  printf("---Test sorted_arrays begin:---\n");
  int A[] = {1, 2, 3, 4, 5};
  int n = sizeof(A) / sizeof(A[0]);
  run_test(A, n, "Sorted Array");
  printf("---Test sorted_arrays end:---\n\n");
}

void test_reverse_sorted() {
  printf("---Test reverse sorted begin:---\n");
  int A[] = {5, 4, 3, 2, 1};
  int n = sizeof(A) / sizeof(A[0]);
  run_test(A, n, "Reverse Sorted");
  printf("---Test reverse_sorted end:---\n\n");
}

void test_same_elements() {
  printf("---Test same_elements begin:---\n");
  int A[] = {7, 7, 7, 7, 7, 7};
  int n = sizeof(A) / sizeof(A[0]);
  run_test(A, n, "Same Elements");
  printf("---Test same_elements end:---\n\n");
}

void test_large_arrays() {
  printf("---Test large_arrays begin:---\n");
  int A[] = {-10, 9, -8, 7, 6, -5, 4, -3, 2, -1, 0};
  int n = sizeof(A) / sizeof(A[0]);
  run_test(A, n, "Large Array With Negative and Positive Numbers");
  printf("---Test large_arrays end:---\n\n");
}

int main() {
  test_small_arrays();
  test_sorted_arrays();
  test_reverse_sorted();
  test_same_elements();
  test_large_arrays();

  printf("Ran %d tests, passed %d tests, failed %d tests.\n", tests_run, tests_passed, tests_failed);
  return 0;
}
  
