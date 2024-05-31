#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hybrid_sort.h"
#include "logger.h"

void insertion_sort(int *A, int left, int right) {
  LOG_OPERATION(2); // for the call to insertionsort
  // Start from the 2nd element of the array
  for (int i = left + 1; i <= right; i++) {
    // Key is the element to be inserted, j is the index for comparison.
    int key = A[i];
    int j = i - 1;
    LOG_OPERATION(1); // For the assignment of the key

    // Shift elements of the sorted segment forward if the are larger than the key.
    while (j >= left && A[j] > key) {
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

// Merges two sorted subarrays of array[].
void hybrid_merge(int *A, int left, int mid, int right) {
  LOG_OPERATION(2); // For dynamically allocating memory for leftHalf and rightHalf
  int leftIdx, rightIdx, mergeIdx;
  // Calculate the size of left subarray.
  int leftSize = mid - left + 1;
  // The size of right subarray.
  int rightSize = right - mid;

  // Dynamically allocate memory for temporary subarrays.
  int *leftHalf = (int *) malloc(leftSize * sizeof(int));
  int *rightHalf = (int *)malloc(rightSize * sizeof(int));

  //Copy data to temp arrays leftHalf[] and rightHalf[]
  for (leftIdx = 0; leftIdx < leftSize; leftIdx++) {
    leftHalf[leftIdx] = A[left + leftIdx];
    LOG_OPERATION(1); // For the assignment.
  }
  for (rightIdx = 0; rightIdx < rightSize; rightIdx++) {
    rightHalf[rightIdx] = A[mid + 1 + rightIdx];
    LOG_OPERATION(1);
  }

  // Merge the temp arrays back into array[left-right]
  leftIdx = 0;
  rightIdx = 0;
  // Start from the left index of the subarray.
  mergeIdx = left;

  // Merge tht 2 arrays by comparing their elements.
  while (leftIdx < leftSize && rightIdx < rightSize) {
    LOG_OPERATION(1); // For the comparison in while condition.
    if (leftHalf[leftIdx] <= rightHalf[rightIdx]) {
      A[mergeIdx] = leftHalf[leftIdx];
      leftIdx++;
    } else {
      A[mergeIdx] = rightHalf[rightIdx];
      rightIdx++;
    }
    LOG_OPERATION(2); // 1 for comparison 1 for assighnment
    mergeIdx++;
  }

  // Copy the remaining elements of leftHalf[], if there are any.
  while (leftIdx < leftSize) {
    A[mergeIdx] = leftHalf[leftIdx];
    leftIdx++;
    mergeIdx++;
    LOG_OPERATION(2);
  }

  // Copy the remaining elements of rightHalf[], if there are any.
  while (rightIdx < rightSize) {
    A[mergeIdx] = rightHalf[rightIdx];
    rightIdx++;
    mergeIdx++;
    LOG_OPERATION(2);
  }

  // Free the memory allocated for temporary arrays.
  free(leftHalf);
  free(rightHalf);
  LOG_OPERATION(2); // For freeing left half and right half.
}

void hybrid_sort(int *A, int left, int right) {
  if (left < right) {
    // Check if sub-array size is at or below crossover point.
    if (right - left + 1 <= 60) {
      // Use insertion sort for small sub arrays
      insertion_sort(A, left, right);
    } else {
      // Continue with merge sort for larger arrays.
      int mid = left + (right - left) / 2;
      hybrid_sort(A, left, mid);
      hybrid_sort(A, mid + 1, right);
      hybrid_merge(A, left, mid, right);
    }
  }
}

void hybrid(int *A, int size) {
  hybrid_sort(A, 0, size - 1);
}
