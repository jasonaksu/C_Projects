#include "quicksort.h"
#include "logger.h"
#include <stdlib.h>
#include <stdbool.h>

// Initialize the random number generator.
void init_rand() {
  // Set seed to 200 for consistent random numbers.
  srand(200);
  LOG_OPERATION(1); // For the call to srand
}

// Function to swap the values of two integers
void swap(int* a, int*b) {
  // Save the value at address 'a' in 'temp'
  int temp = *a;
  // Assign the value at address 'b' to address 'a'
  *a = *b;
  // Assign the value saved in 'temp' to address 'b'
  *b = temp;
  LOG_OPERATION(3);
}

// Hoare's partition scheme
int hoarePartition(int *A, int low, int high) {
  // Random pivot selection from the Array
  int pivotIdx =  low + (rand() % (high - low + 1));
  int pivot = A[pivotIdx];
  LOG_OPERATION(2); // For the calculation of pivotIdx and pivot assignment
  
  // Initialize left pointer
  int i = low - 1;
  // Initialize right pointer.
  int j = high + 1;

  // Loop indefinitely.
  while (true) {
    // Find leftmost element greater than or equal to pivot.
    while (i < high && A[++i] < pivot);

    // Find rightmost element less than or equal to pivot.
    while (j > low && A[--j] > pivot);
    
    // If pointer is crossed , partitioning is complete
    if (i >= j) {
      LOG_OPERATION(1); // For the final comparison.
      // Return the partition point.
      return j;
    }

    // Swap the elements on wrong sides.
    swap(&A[i], &A[j]);
  }
}

// Recursive quicksort function.
void recursive_qs(int *A, int low, int high) {
  // Base condition: if there are at least two elements to sort.
  if (low < high) {
    // Partition the array and obtain the partition point.
    int pivot = hoarePartition(A, low, high);
    LOG_OPERATION(1);

    // Recursively apply quicksort to the left of the pivot.
    recursive_qs(A, low, pivot);
    // Recursively apply quicksort to the right of the pivot.
    recursive_qs(A, pivot + 1, high);
  }
}

void quicksort(int *A, int size) {
  // Initialize the random number generator.
  init_rand();
  LOG_OPERATION(1);
  // start the recursive quick sort process.
  recursive_qs(A, 0, size - 1);
}
