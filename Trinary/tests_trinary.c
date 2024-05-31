#include <stdio.h>

/*
  Compile this test file with the following command
  gcc binsearch.c tests_trinary.c -o tests_trinary
*/

extern int trinary_search(int A[], int n, int element);

// Funtion prototypes for test cases.
int found_middle();
int found_first();
int found_last();
int not_found();
int empty_array();
int single_element();
int negative_and_zero();
int repeated_elements();

int found_middle() {
  printf("---Test found_middle begin:---\n");
  int A[] = {1, 2, 3, 4, 5};
  int result = trinary_search(A, 5, 3);
  printf("---Test found_middle end:---\n");
  return result == 2;
}

int found_first() {
  printf("---Test found_first begin: ---\n");
  int A[] = {1, 2, 3, 4, 5};
  int result = trinary_search(A, 5, 1);
  printf("---Test found_first end:---\n");
  return result == 0;
}

int found_last() {
  printf("---Test found_last begin:---\n");
  int A[] = {1, 2, 3, 4, 5};
  int result = trinary_search(A, 5, 5);
  printf("---Test found_last end:---\n");
  return result == 4;
}

int element_at_mid1() {
  printf("---Test element_at_mid1 begin:---\n");
  int A[] = {1, 2, 3, 4, 5, 6, 7};
  int result = trinary_search(A, 7, 2);
  printf("---Test element_at_mid1 end:---\n");
  return result == 1;
}

int element_at_mid2() {
  printf("---Test element_at_mid2 begin:---\n");
  int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int result = trinary_search(A, 9, 7);
  printf("---Test element_at_mid2 end:---\n");
  return result == 6;
}
int not_found() {
  printf("---Test not_found begin:---\n");
  int A[] = {1, 2, 3, 4, 5};
  int result = trinary_search(A, 5, 6);
  printf("---Test not_found end:---\n");
  return result == -1;
}

int empty_array() {
  printf("---Test empty_array begin:---\n");
  int A[] = {};
  int result = trinary_search(A, 0, 1);
  printf("---Test empty_array end:---\n");
  return result == -1;
}

int single_element() {
  printf("---Test single_element begin:---\n");
  int A[] = {1};
  int result = trinary_search(A, 1, 1);
  printf("---Test single_element end:---\n");
  return result == 0;
}

int negative_and_zero() {
  printf("---Test negative_and_zero begin:---\n");
  int A[] = {-5, -3, -1, 0, 2, 4, 6};
  int target_negative = -3;
  int target_zero = 0;
  int result_negative = trinary_search(A, 7, target_negative);
  int result_zero = trinary_search(A, 7, target_zero);
  printf("---Test negative_and_zero end:---\n");
  return (result_negative == 1) && (result_zero == 3);
}

int repeated_elements() {
  printf("---Test repeated_element begin:---\n");
  int A[] = {1, 2, 2, 3, 4, 5};
  int target = 2;
  int result = trinary_search(A, 6, target);
  printf("---Test repeated_element begin:---\n");
  return result == 1;
}

int main() {
  int total_tests = 10;
  int passed_tests = 0;

  passed_tests += found_middle();
  passed_tests += found_first();
  passed_tests += found_last();
  passed_tests += element_at_mid1();
  passed_tests += element_at_mid2();
  passed_tests += not_found();
  passed_tests += empty_array();
  passed_tests += single_element();
  passed_tests += negative_and_zero();
  passed_tests += repeated_elements();

  int failed_tests = total_tests - passed_tests;

  printf("\nRan %d tests, passed %d tests, failed %d tests\n", total_tests, passed_tests, failed_tests);
  return 0;
}
