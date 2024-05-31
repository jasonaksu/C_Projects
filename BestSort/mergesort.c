#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"
#include "logger.h"

// Merges two sorted subarrays of array[].
void merge(int *A, int left, int mid, int right) {
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

// Recursive mergesort (top-down)
void aksuMergesort(int *A, int size) {
  LOG_OPERATION(2); // Function call to aksuMergesort
  // Base case: if the array is 1 or 0 elements long, its already sorted.
  if (size < 2) {
    LOG_OPERATION(1); // For the return statement in base case.
    return;
  }
  // Calculate the middle index of the array.
  int mid = size / 2;

  // Recursively sort the left and right half of the array
  aksuMergesort(A, mid);
  aksuMergesort(A + mid, size - mid);

  // Merge the sorted halves
  merge(A, 0, mid -1, size - 1);

  LOG_OPERATION(1);
}
