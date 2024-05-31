#include "insertionsort.h"
#include "logger.h"

void insertionsort(int *A, int size) {
  LOG_OPERATION(2); // for the call to insertionsort
  // Start from the 2nd element of the array
  for (int i = 1; i < size; i++) {
    // Key is the element to be inserted, j is the index for comparison.
    int key = A[i];
    int j = i - 1;
    LOG_OPERATION(1); // For the assignment of the key

    // Shift elements of the sorted segment forward if the are larger than the key.
    while (j >= 0 && A[j] > key) {
      // Shift the element one position to the right.
      A[j + 1] = A[j];
      // Move to the next element on the left
      j = j - 1;
      LOG_OPERATION(2); // 1 for comparison, 1 for assignment
    }

    // Insert the key at its correct position in the sorted segment
    A[j + 1] = key;
    LOG_OPERATION(1); // For the final assignment
  }
  LOG_OPERATION(1); // For the return statement
}
