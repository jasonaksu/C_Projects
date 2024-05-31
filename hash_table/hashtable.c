#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

// Hash function to use first and last character of the string.
int hashFirstLast(char *str, int buckets) {
  // Handle empty strings to avoid out of bounds access.
  if (strlen(str) == 0) return 0;
  int firstChar = str[0];
  int lastChar = str[strlen(str) -1];
  int middleChar = str[strlen(str) / 2];// Middle works for even and odd lengths
  
  // Calculate avarage of  first, last and mid chars.
  int average = ((firstChar + lastChar + middleChar) / 3);

  // Calculate hash index
  int index = average % buckets;
  
  return index;
}

// Create a new hash table with the specific number of buckets.
hashtable_t *create_hashtable(int buckets) {
  // Allocate memory of the hash table.
  hashtable_t *hashTable = (hashtable_t *)malloc(sizeof(hashtable_t));
  // Check for succesfull allocation.
  if (!hashTable) return NULL;

  // Allocate array for the buckets.
  hashTable->buckets = (node_t **) malloc(sizeof(node_t*) * buckets);
  if (!hashTable->buckets) {
    // Free the table if bucket allocation fails.
    free(hashTable);
    return NULL;
  }
  for (int i = 0; i< buckets; i++) {
    // Initialize all buckets to NULL
    hashTable->buckets[i] = NULL;
  }

  // Set the number of buckets.
  hashTable->no_of_buckets = buckets;
  // Assign the hash function
  hashTable->hash_function = hashFirstLast;

  // return the pointer to the hash table
  return hashTable;
}

// Add an entry to the hash table if it does not already exist.
void hashtable_add(hashtable_t *table, char *entry) {
  // Get bucket index for entry.
  int index = table->hash_function(entry, table->no_of_buckets);
  // Pointer to the bucket.
  node_t **bucket = &table->buckets[index];

  // Check if the entry already exist in the bucket.
  while (*bucket) {
    // Entry found do nothing.
    if (strcmp((*bucket)->data, entry) == 0) return;
    // Move to the next node.
    bucket  = &(*bucket)->next;
  }

  // Entry not found add new node to the bucket.
  node_t *newNode = (node_t *)malloc(sizeof(node_t));
  // Check for allocation failure.
  if (!newNode) return;
  // Duplicate entry str.
  newNode->data = strdup(entry);
  newNode->next = NULL; // Set next to the NULL.
  *bucket = newNode; // Link new node.
}

// Check if an entry exist in the hash table.
bool hashtable_contains(hashtable_t *table, char *entry) {
  // Get bucket index for entry
  int index = table->hash_function(entry, table->no_of_buckets);
  // Pointer to start of bucket.
  node_t *current = table->buckets[index];

  // Search for entry in the bucket.
  while (current) {
    // Entry found.
    if(strcmp(current->data, entry) == 0) return true;
    current = current->next;
  }
  return false; // Entry not found.
}

// delete the hash table and free all allocated resources.
void delete_hashtable(hashtable_t *table) {
  // Iterate all over the buckets.
  for (int i = 0; i < table->no_of_buckets; i++) {
    node_t *current = table->buckets[i], *temp;
    // Free all nodes in the current bucket.
    while (current) {
      temp = current;
      // Move to the next node.
      current = current->next;
      // free the str data.
      free(temp->data);
      // Free the node.
      free(temp);
    }
  }
  // Free the bucket array.
  free(table->buckets);
  // Free the table structure.
  free(table);
}
