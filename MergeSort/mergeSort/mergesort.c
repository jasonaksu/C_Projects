#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"

// Merges two sorted subarrays of array[].
void merge(char **array, int left, int mid, int right) {
  int leftIdx, rightIdx, mergeIdx;
  // Calculate the size of left subarray.
  int leftSize = mid - left + 1;
  // The size of right subarray.
  int rightSize = right - mid;

  // Dynamically allocate memory for temporary subarrays.
  char **leftHalf = (char **) malloc(leftSize * sizeof(char *));
  char **rightHalf = (char **)malloc(rightSize * sizeof(char *));

  //Copy data to temp arrays leftHalf[] and rightHalf[]
  for (leftIdx = 0; leftIdx < leftSize; leftIdx++)
    leftHalf[leftIdx] = array[left + leftIdx];
  for (rightIdx = 0; rightIdx < rightSize; rightIdx++)
    rightHalf[rightIdx] = array[mid + 1 + rightIdx];

  // Merge the temp arrays back into array[left-right]
  leftIdx = 0;
  rightIdx = 0;
  // Start from the left index of the subarray.
  mergeIdx = left;

  // Merge tht 2 arrays by comparing their elements.
  while (leftIdx < leftSize && rightIdx < rightSize) {
    if (strcmp(leftHalf[leftIdx], rightHalf[rightIdx]) > 0) {
      array[mergeIdx] = leftHalf[leftIdx];
      leftIdx++;
    } else {
      array[mergeIdx] = rightHalf[rightIdx];
      rightIdx++;
    }
    mergeIdx++;
  }

  // Copy the remaining elements of leftHalf[], if there are any.
  while (leftIdx < leftSize) {
    array[mergeIdx] = leftHalf[leftIdx];
    leftIdx++;
    mergeIdx++;
  }

  // Copy the remaining elements of rightHalf[], if there are any.
  while (rightIdx < rightSize) {
    array[mergeIdx] = rightHalf[rightIdx];
    rightIdx++;
    mergeIdx++;
  }

  // Free the memory allocated for temporary arrays.
  free(leftHalf);
  free(rightHalf);
}

// Recursive mergesort (top-down)
void td_mergesort(char **strings, int size) {
  // Base case: if the array is 1 or 0 elements long, its already sorted.
  if (size < 2) {
    return;
  }
  // Calculate the middle index of the array.
  int mid = size / 2;

  // Recursively sort the left and right half of the array
  td_mergesort(strings, mid);
  td_mergesort(strings + mid, size - mid);

  // Merge the sorted halves
  merge(strings, 0, mid -1, size - 1);
}

// Utility function to find minimum of two integers
int min(int x, int y) {
  return (x < y) ? x : y;
}

// Iterative mergesort (bottom-up)
void bu_mergesort(char **strings, int n) {
  int currentSize; // Size of subarrays to merge.
  int left_start; // Starting index of left subarray to merge.

  // Double the size of subarrays to merge each iteration.
  for (currentSize = 1; currentSize <= n-1; currentSize = 2*currentSize) {
    // Merge subarrays in currentSize
    for (left_start = 0; left_start < n-1; left_start += 2*currentSize) {
      // Calculate middle and right indices for merge.
      int mid = min(left_start + currentSize - 1, n-1);
      int right_end = min(left_start + 2*currentSize - 1, n-1);

      // Merge the subarrays.
      merge(strings, left_start, mid, right_end);
    }
  }
}
