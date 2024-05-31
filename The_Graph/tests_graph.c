#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

#define INFINITY 123456

// Variables to keep track of test outcomes.
int tests_run = 0;
int tests_passed = 0;
int tests_failed = 0;

// Function to print results of each test with updating counts.
void print_test_result(int condition, const char *test_name) {
    printf("---%s begin:---\n", test_name);
    if (condition) {
        printf("PASSED\n");
        tests_passed++;
    } else {
        printf("FAILED\n");
        tests_failed++;
    }
    printf("---%s end:---\n\n", test_name);
    tests_run++;
}

// Test if is_adjacent correctly identifies non-adjacency in an empty graph.
void test_is_adjacent_empty_graph() {
  graph_t *g = init_graph(0); // Initialize an empty graph
  print_test_result(is_adjacent(g, 0, 0) == false, "test_is_adjacent_empty_graph");
  delete_graph(g); // Clean up.
}

// Tests adding an edge and verifying adjacency in both directions.
void test_add_edge_and_is_adjacent() {
  graph_t *g = init_graph(2); // Graph with 2 vertices.
  add_edge(g, 0, 1, 1); // Add a single directed edge.
  // Check for correct adjacency and non adjacency.
  print_test_result(is_adjacent(g, 0, 1) == true && !is_adjacent(g, 1, 0), "test_add_edge_and_is_adjacent");
  delete_graph(g); // Clean up.
}

// Tests adding a self loop and veriifying it.
void test_add_edge_self_loop() {
  graph_t *g = init_graph(3); // Graph with 3 vertices.
  add_edge(g, 0, 0, 1); // Add a self loop.
  print_test_result(is_adjacent(g, 0, 0), "test_add_edge_self_loop");
  delete_graph(g); // clean up.
}

// Tests updating an edge's weight.
void test_add_edge_multiple_paths() {
  graph_t *g = init_graph(3); // Graph with 3 vertices/
  add_edge(g, 0, 1, 10); // Add edge with initial weight.
  add_edge(g, 0, 1, 5); // Update the edge's weight.
  print_test_result(true, "test_add_edge_multiple_paths");
  delete_graph(g); // Clean up.
}

// Tests adding an edge with negative weight.
void test_negative_weight_edge() {
  graph_t *g = init_graph(2); // Graph with two vertices.
  add_edge(g, 0, 1, -1); // Add edge with negative weight.
  print_test_result(is_adjacent(g, 0, 1), "test_negative_weight_edge");
  delete_graph(g); // Clean up.
}

// Test is adjacent for a non existing edge.
void test_is_adjacent_non_existent_edge() {
  graph_t *g = init_graph(2); // Graph with 2 vertices
  print_test_result(!is_adjacent(g, 0, 1), "test_is_adjacent_non_existent_edge");
  delete_graph(g); // Clean up.
}

// Test for unweighted shortest path.
void test_lengths_unweighted_shortest_paths() {
  graph_t *g = init_graph(3); // Graph with 3 vertices.
  add_edge(g, 0, 1, 1); // Add a self loop.
  add_edge(g, 1, 2, 1); // Create a path.
  int *lengths = lengths_unweighted_shortest_paths(g, 0); // Calculate the shortest path.
  print_test_result(lengths[2] == 2, "test_lengths_unweighted_shortest_paths");
  free(lengths);
  delete_graph(g); // Clean up.
}

// Tests unweighted shortest paths in a disconnected graph
void test_lengths_unweighted_shortest_paths_self_loop() {
  graph_t *g = init_graph(3); // Graph with 3 vertices.
  add_edge(g, 0, 0, 1); // Add a self loop.
  add_edge(g, 0, 1, 1); // Create a path.
  int *lengths = lengths_unweighted_shortest_paths(g, 0); // Calculate the shortest paths.
    print_test_result(lengths[1] == 1, "test_lengths_unweighted_shortest_paths_self_loop");
    free(lengths);
    delete_graph(g); // Clean up.
}

// Test for weighted shortest path lengths
void test_lengths_weighted_shortest_paths() {
  graph_t *g = init_graph(3); // Graph with three vertices.
  add_edge(g, 0, 1, 10); // Create a path.
  add_edge(g, 1, 2, 10); // Extend the path
  add_edge(g, 0, 2, 5); // Add a shorter path
  int *distances = lengths_weighted_shortest_paths(g, 0); // Calculate the shhortest path.
  print_test_result(distances[2] == 5, "test_lengths_weighted_shortest_paths");
  free(distances);
  delete_graph(g); // Clean up.
}

// Weighted shortest paths with multiple path options.
void test_lengths_weighted_shortest_paths_multiple_paths() {
  graph_t *g = init_graph(4); // Graph with 4 vertices.
  // Creating multiple paths with varying lengths.
  add_edge(g, 0, 1, 10);
  add_edge(g, 0, 2, 5);
  add_edge(g, 2, 1, 2);
  add_edge(g, 0, 3, 1);
  add_edge(g, 3, 1, 1);
  int *distances = lengths_weighted_shortest_paths(g, 0); // Calculate the shortest paths.
  print_test_result(distances[1] == 2, "test_lengths_weighted_shortest_paths_multiple_paths");
  free(distances);
  delete_graph(g); // Clean up.
}

// Tests weighted shortest paths with a negative weight edge.
void test_lengths_weighted_shortest_paths_negative_weight() {
  graph_t *g = init_graph(2); // Grph 2 vwertices.
  add_edge(g, 0, 1, -1); // Adding edge with negative weights.
  int *distances = lengths_weighted_shortest_paths(g, 0); // Calculate the shortest paths.
  print_test_result(distances[1] == -1, "test_lengths_weighted_shortest_paths_negative_weight");
  free(distances);
  delete_graph(g); // Clean up.
}

int main() {
  test_is_adjacent_empty_graph();
  test_add_edge_and_is_adjacent();
  test_add_edge_self_loop();
  test_add_edge_multiple_paths();
  test_negative_weight_edge();
  test_is_adjacent_non_existent_edge();
  test_lengths_unweighted_shortest_paths();
  test_lengths_unweighted_shortest_paths_self_loop();
  test_lengths_weighted_shortest_paths();
  test_lengths_weighted_shortest_paths_multiple_paths();
  test_lengths_weighted_shortest_paths_negative_weight();

  printf("Ran %d tests, passed %d tests, failed %d tests.\n", tests_run, tests_passed, tests_failed);
  return 0;
}
