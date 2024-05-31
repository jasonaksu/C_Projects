#include <stdio.h>

// Function Prototypes.
int trinary_search(int A[], int n, int element);
int crossover(int A[], int n);

int trinary_search(int A[], int n, int element) {
    // Initialize the search bounds.
    int left = 0, right = n - 1;
    //Continue until bounds overlap.
    while (left <= right) {
        // Calculate the required two midpoints.
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) /3;

        // Check if either midpoint conatines the target element
        if(A[mid1] == element) {
            return mid1; // Element found at mid 1
        }
        if (A[mid2] == element) {
            return mid2; // Element found at mid 2
        }

        // Narrow the search range based on midpoints.
        if (element < A[mid1]) {
            // Target is between left and mid1.
            right = mid1 -  1;
        } else if (element > A[mid2]) {
            // target is between mid2 and right
            left = mid2 + 1;
        } else {
            // Target is between mid1 and mid2.
            left = mid1 + 1;
            right = mid2 - 1;
        }
    }
    // Element not found
    return -1;
}

// Crossover function to find the index of the first negative number.
int crossover(int A[], int n) {
    // Initialize the search bounds
    int left = 0, right = n - 1;
    // Continue until bounds over lap.
    while (left <= right) {
        // Calculate midpoint for binary search
        int mid = left + (right - left) / 2;

        // Determine if the midpoint is positive, so first negative number is further right.
        if (A[mid] > 0) {
            // Continue searc in the right half.
            left = mid + 1;
        } else {
            // The current number is negative. Check if it is the first negative.
            if (mid == 0 || A[mid -1] > 0) {
                // this is the first negative number.
                return mid;
            }
            // Else continue search in the left half.
            right = mid - 1;
        }
    }

    // If there are no negative number
    return -1;
}
