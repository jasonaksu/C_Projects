#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"

typedef void (*SortFunction)(char **, int);

// Function to print string arrays.
void print(char *arr[], int n) {
  for (int i = 0; i < n; i++)
    printf("%s ", arr[i]);
  printf("\n");
}

// Function to run a single test case
void runTest(SortFunction sortFunc, char *arr[], int n, const char *description) {
    printf("%s:\nOriginal: ", description);
    for (int i = 0; i < n; i++) printf("%s ", arr[i]);
    printf("\n");

    // Sort the array using the provied function.
    sortFunc(arr, n);
    
    printf("Sorted:   ");
    for (int i = 0; i < n; i++) printf("%s ", arr[i]);
    printf("\n\n");
}

int main() {
  // Test data
  char *sortedAsc[] = {"black", "eagle", "flies", "high"};
  int nAsc = sizeof(sortedAsc) / sizeof(sortedAsc[0]);
 
  char *sortedDsc[] = {"white", "the", "greatest", "champion", "black", "besiktas"};
  int nDsc = sizeof(sortedDsc) / sizeof(sortedDsc[0]);

  char *empty[] = {};
  int nEmpty = sizeof(empty) / sizeof(empty[0]);

  char *sameElements[] = {"eagle", "eagle", "eagle", "eagle"};
  int nSame = sizeof(sameElements) / sizeof(sameElements[0]);

  char *single[] = {"eagle"};
  int nSingle = sizeof(single) / sizeof(single[0]);

  char *random[] = {"flies", "eagle", "black", "high"};
  int nRandom = sizeof(random) / sizeof(random[0]);


  // Testing for td_mergesort
  printf("---Testing td_mergesort begin:---\n");
  runTest(td_mergesort, sortedAsc, nAsc, "Sorted in Ascending Order");
  runTest(td_mergesort, sortedDsc, nDsc, "Sorted in Descending Order");
  runTest(td_mergesort, empty, nEmpty, "Empty Array");
  runTest(td_mergesort, sameElements, nSame, "Same Elements");
  runTest(td_mergesort, single, nSingle, "Single Element");
  runTest(td_mergesort, random, nRandom, "Random Order");
  printf("---Testing td_mergesort end:---\n");

  printf("\n");

  // Reset arrays to their original version.
  char *sortedAscReset[] = {"black", "eagle", "flies", "high"};
  char *sortedDscReset[] = {"white", "the", "greatest", "champion", "black", "besiktas"};
  char *emptyReset[] = {};
  char *sameElementsReset[] = {"eagle", "eagle", "eagle", "eagle"};
  char *singleReset[] = {"eagle"};
  char *randomReset[] = {"flies", "eagle", "black", "high"};
  memcpy(sortedAsc, sortedAscReset, sizeof(sortedAscReset));
  memcpy(sortedDsc, sortedDscReset, sizeof(sortedDscReset));
  memcpy(empty, emptyReset, sizeof(emptyReset));
  memcpy(sameElements, sameElementsReset, sizeof(sameElementsReset));
  memcpy(single, singleReset, sizeof(singleReset));
  memcpy(random, randomReset, sizeof(randomReset));

  // Testing for bu_mergesort.
  printf("---Testing bu_mergesort begin:---\n");
  runTest(bu_mergesort, sortedAsc, nAsc, "Sorted in Ascending Order");
  runTest(bu_mergesort, sortedDsc, nDsc, "Sorted in Descending Order");
  runTest(bu_mergesort, empty, nEmpty, "Empty Array");
  runTest(bu_mergesort, sameElements, nSame, "Same Elements");
  runTest(bu_mergesort, single, nSingle, "Single Element");
  runTest(bu_mergesort, random, nRandom, "Random Order");
  printf("---Testing bu_mergesort end:---\n");

  return 0;
}
