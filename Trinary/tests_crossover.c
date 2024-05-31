#include <stdio.h>

/*
  Compile this file with the following command.
  gcc binsearch.c tests_crossover.c -o tests_crossover
*/

extern int crossover(int A[], int n);

// Function prototypes
int test_first_negative_middle();
int test_all_positive();
int test_all_negative();
int test_single_positive();
int test_single_negative();

int test_first_negative_middle() {
  printf("---Test test_first_negative_middle begin:---\n");
  int A[] = {1, 2, 3, -1, -2, -3};
  int result = crossover(A, 6);
  printf("---Test test_first_negative_middle end:---\n");
  return result == 3;
}

int test_all_positive() {
  printf("---Test test_all_positive begin:---\n");
  int A[] = {1, 2, 3, 4, 5};
  int result = crossover(A, 5);
  printf("---Test test_all_positive end:---\n");
  return result == -1;
}

int test_all_negative() {
  printf("---Test test_all_negative begin:---\n");
  int A[] = {-1, -2, -3, -4, -5};
  int result = crossover(A, 5);
  printf("---Test test_all_negative end:---\n");
  return result == 0;
}

int test_single_positive() {
  printf("---Test test_single_positive begin:---\n");
  int A[] = {1};
  int result = crossover(A, 1);
  printf("---Test test_single_positive end:---\n");
  return result == -1;
}

int test_single_negative() {
  printf("---Test test_single_negative begin:---\n");
  int A[] = {-1};
  int result = crossover(A, 1);
  printf("---Test test_single_negative end:---\n");
  return result == 0;
}

int main() {
  int total_tests = 5;
  int passed_tests = 0;

  passed_tests += test_first_negative_middle();
  passed_tests += test_all_positive();
  passed_tests += test_all_negative();
  passed_tests += test_single_positive();
  passed_tests += test_single_negative();

  int failed_tests = total_tests- passed_tests;

  printf("\nRan %d tests, passed %d tests, failed %d tests\n", total_tests, passed_tests, failed_tests);
  return 0;
}
