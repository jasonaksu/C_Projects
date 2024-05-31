#include "random_data.h"
#include <stdlib.h>

int *random_data(int n) {
  // Allocate memory for the array
  int *array = malloc(n * sizeof(int));
  if (array == NULL) {
    // Return NULL when memory allocation failed
    return NULL;
  }

  // Populate the array with random numbers
  for (int i = 0; i < n; i++) {
    // Using rand() to generate a random number.
    array[i] = rand();
  }

  return array;
}
