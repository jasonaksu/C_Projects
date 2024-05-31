#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"
#include "random_data.h"
#include "quicksort.h"
#include "insertionsort.h"
#include "mergesort.h"
#include "hybrid_sort.h"

/* Compile this file with the following command
   gcc best_sorting_test.c hybrid_sort.c insertionsort.c mergesort.c quicksort.c logger.c random_data.c -o sort_test
*/


// Main function to test and compare insertion sort, merge sort and hybrid sort with different data sizes.
int main() {
    // Sizes of arrays to test sorting algorithms with
  int test_sizes[] = {2, 5, 10, 50, 60, 70, 100, 500, 1903, 10000, 100000, 500000};
    int num_tests = sizeof(test_sizes) / sizeof(test_sizes[0]);  // Number of tests to run

    // Loop over each test size and sort arrays of that size
    for (int i = 0; i < num_tests; i++) {
        int size = test_sizes[i];  // Current size to test
	printf("\n");
        printf("~~~~~~Test sorting with array size: %d~~~~~~\n", size);

        // Repeat the test 5 times for each size to get a good average
        for (int test = 1; test <= 5; test++) {
            printf("  Test %d\n", test);

            // Create a random array of the current size
            int* array = random_data(size);
            if (array == NULL) {
                printf("~~~Failed to allocate memory for the array.~~~\n");
                continue;  // Skip to the next trial
            }

            // Create a copy of the array for all algorithms to test
            int* array_copy = malloc(size * sizeof(int));
            if (array_copy == NULL) {
                printf("~~~Failed to allocate memory for the array copy.~~~\n");
                free(array);  // Release the memory of the first array
                continue;  // Skip to the next trial
            }


	    // Test Quick sort
	    memcpy(array_copy, array, size * sizeof(int));  // Copy the original array
            logger_reset();  // Reset the logger to start counting from zero
            quicksort(array_copy, size);  // Sort the copy
            printf("    Quick Sort Steps: %d\n", logger.num_steps);
	    
            // Test insertion sort
            memcpy(array_copy, array, size * sizeof(int));  // Copy the original array
            logger_reset();  // Reset the logger to start counting from zero
            insertionsort(array_copy, size);  // Sort the copy
            printf("    Insertion Sort Steps: %d\n", logger.num_steps);

            // Test merge sort
            memcpy(array_copy, array, size * sizeof(int));  // Copy the original array
            logger_reset();  // Reset the logger to start counting from zero
            aksuMergesort(array_copy, size);  // Sort the copy
            printf("    Merge Sort Steps: %d\n", logger.num_steps);

	    // Test hybrid sort.
	    memcpy(array_copy, array, size * sizeof(int));  // Copy the original array
	    logger_reset();  // Reset the logger to start counting from zero
	    hybrid(array_copy, size);  // Sort the copy
	    printf("    Hybrid Sort Steps: %d\n", logger.num_steps);

            // Clean up memory
            free(array);
            free(array_copy);
        }
    }

    return 0;
}
