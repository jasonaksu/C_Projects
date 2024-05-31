#include <stdio.h>
#include "hashtable.h"

/*
  Compile this file with following command.
  gcc tests_hashtable.c hashtable.c -o tests_hashtable
*/


// Test for adding entries and check their presence.

int testAddCheck() {
  printf("---Test testAddCheck begin:---\n");
  // Create hash table with 10 buckets.
  hashtable_t *table = create_hashtable(10);

  // Adding entries.
  hashtable_add(table, "black");
  hashtable_add(table, "eagle");
  hashtable_add(table, "fly");
  hashtable_add(table, "high");

  // Check presence.
  int passed = 1;
  if (!hashtable_contains(table, "black")) {
    printf("Test failed: 'black' should be present\n");
    passed = 0;
  }

  if (!hashtable_contains(table, "eagle")) {
    printf("Test failed: 'eagle' should be present\n");
    passed = 0;
  }

  if (hashtable_contains(table, "lion")) {
    printf("Test failed: 'lion' should not be present\n");
    passed = 0;
  }

  // Clean up.
  delete_hashtable(table);
  printf("---Test testAddCheck end:---\n");
  return passed;
}

// Test for hash table initialization and deletion without entries.
int testInitDelete() {
  printf("---Test testInitDelete begin:---\n");
  // Create hash table with 5 buckets.
  hashtable_t *table = create_hashtable(5);

  if (!table) {
    printf("---Test failed: Hash table was not created\n");
    return 0;
  }

  // The table should be empty here.
  if (hashtable_contains(table, "anything")) {
    printf("Test failed: Hash table should be empty\n");
    delete_hashtable(table);
    return 0;
  }

  delete_hashtable(table);
  printf("---Test testInitDelete end:---\n");
  return 1;
}

// Main function to run test cases and provide summary.
int main() {
  int total_tests = 2;
  int tests_passed = 0;

  tests_passed += testAddCheck();
  tests_passed += testInitDelete();

  printf("Ran %d tests, passed %d tests, failed %d tests\n", total_tests, tests_passed, total_tests - tests_passed);
  return 0;
}
