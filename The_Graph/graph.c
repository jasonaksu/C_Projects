#include "graph.h"
#include <stdlib.h>
#include <stdbool.h>

#define INFINITY 123456

// Create a graph of the given number of vertices. 
graph_t *init_graph(int num_vertices) {
  // Allocate memory for the graph structure
  graph_t *graph = (graph_t *)malloc(sizeof(graph_t));
  if (!graph) return NULL;
  // Set the numer of vertices.
  graph->num_vertices = num_vertices;
  // Initially graph has no edges
  graph->num_edges = 0;
  // Allocate memory for the adjacency list array, one entry per vertex.
  graph->adj_list = (dnode_t **)calloc(num_vertices, sizeof(dnode_t *));
  if (!graph->adj_list) {
    free(graph);
    return NULL;
  }
  return graph;
}
  
// Delete the specified graph and free its memory.
void delete_graph(graph_t *g) {
  // Check if the graph pointer is NULL.
  if (g == NULL) return;

  // Iterate through each vertex's adjacency list.
  for (int i = 0; i < g->num_vertices; i++) {
    // Get the head of the adjacency list for vertex i
    dnode_t *current = g->adj_list[i];
    while (current != NULL) {
      // Temporarily store the current node.
      dnode_t *temp = current;
      // Move to the next node in the list.
      current = current->next;
      // Free the temporary node.
      free(temp);
    }
  }

  // Free the array of the lists head.
  free(g->adj_list);
  // Free the graph structure
  free(g);
}

// This function can insert the vertices in each other's adjacency lists in any order.  
void add_edge(graph_t *graph,int u,int v,int weight) {
  // Validate vertices
  if (u < 0 || u >= graph->num_vertices || v < 0 || v >= graph->num_vertices) return;

  // Check if an edge from u to v already exist.
  dnode_t *temp = graph->adj_list[u];
  while (temp != NULL) {
    if (temp->destination == v) {
      // Edge exists update the weight.
      temp->weight = weight;
      // Exit the function.
      return;
    }
    temp = temp->next;
  }

  // If no existing edge found, add a new edge.
  // Allocate the memory for the new edge.
  dnode_t *newNode = (dnode_t *)malloc(sizeof(dnode_t));
  if (!newNode) return;
  
  // Set destination vertex
  newNode->destination = v;
  // Set weight of the edge
  newNode->weight = weight;
  // Insert the new node at the beginning.
  newNode->next = graph->adj_list[u];
  // Prev is NULL inserted at the head
  newNode->prev = NULL;

  // If there is already a node, update prev pointer.
  if (graph->adj_list[u] != NULL) {
    graph->adj_list[u]->prev = newNode;
  }

  // Update the head of the adj list.
  graph->adj_list[u] = newNode;

  // Increment the edge count.
  graph->num_edges++;
}

bool is_adjacent(graph_t *graph, int u, int v) {
  // Validate vertex identifiers
  if (u < 0 || u >= graph->num_vertices || v < 0 || v >= graph->num_vertices) return false;

  // Start at the head of u's adjacency list.
  dnode_t *temp = graph->adj_list[u];
  // Traverse the list
  while (temp != NULL) {
    // If an edge to v is found, return true.
    if (temp->destination == v) return true;
    // Move to the next node in the list.
    temp = temp->next;
  }
  // If no edge to v is found
  return false;
}


// This function will ignore the weights of an edge (or in other words, assume all weights are 1)
int *lengths_unweighted_shortest_paths(graph_t *graph,int from) {
  // Allocate memory for the shortest path length.
  int *shortest = (int *)malloc(graph->num_vertices * sizeof(int));
  if (!shortest) return NULL;
  
  for (int i = 0; i < graph->num_vertices; i++) {
    // Initialize distances to INFINITY. (123456)
    shortest[i] = INFINITY;
  }
  // Distance from source the itself = 0
  shortest[from] = 0;

  //Tracking parent.
  int *queue = (int *)malloc(graph->num_vertices * sizeof(int));
  if (!queue) {
    free(shortest);
    return NULL;
  }
  
  // Queue initialization.
  int front = 0, rear = 0;
  // Enqueue source vertex.
  queue[rear++] = from;

  // While the queue is not empty
  while (front < rear) {
    // Dequeue a vertex
    int current = queue[front++];
    for (dnode_t *temp = graph->adj_list[current]; temp != NULL; temp = temp->next) {
      // If the vertex is not visited.
      if (shortest[temp->destination] == INFINITY) {
	// Update shortest path length.
	shortest[temp->destination] = shortest[current] + 1;
	// Enqueue vertex.
	queue[rear++] = temp->destination;
	
      }
    }
  }

  // Free the queue
  free(queue);
  // Return the array of the shortest path lengths.
  return shortest;
}

void updatePriorityQueue(int *pq, int *distances, int num_vertices) {
    // Perform insertion sort on the priority queue based on current distances
    for (int i = 1; i < num_vertices; i++) {
        int key = pq[i];
        int j = i - 1;

        // Shift elements of the priority queue that have greater distances than the key
        while (j >= 0 && distances[pq[j]] > distances[key]) {
            pq[j + 1] = pq[j];
            j = j - 1;
        }
        // Place the key in its correct sorted position
        pq[j + 1] = key;
    }
}

// Extracts the vertex with the minimum distance that hasn't been visited.
int extMin(int *pq, bool *visited, int *distances, int num_vertices) {
    for (int i = 0; i < num_vertices; i++) {
        int u = pq[i];
        // Return the first unvisited vertex in the priority queue and mark it as visited
        if (!visited[u]) {
            visited[u] = true; // Mark this vertex as visited
            return u;
        }
    }
    // Return -1 if all vertices have been visited or if the queue is empty
    return -1;
}

// Implements Dijkstra's algorithm to find the shortest paths from a given vertex.
int *lengths_weighted_shortest_paths(graph_t *graph, int from) {
    // Allocate memory for distances and visited status for each vertex
  int *distances = (int *)malloc(graph->num_vertices * sizeof(int));
  if (!distances) return NULL;

  bool *visited = (bool *)malloc(graph->num_vertices * sizeof(bool));
  if (!visited) {
    free(distances);
    return NULL;
  }

  int *priorityQueue = (int *)malloc(graph->num_vertices * sizeof(int));
  if (!priorityQueue) {
    free(distances);
    free(visited);
    return NULL;
  }

  // Initialize distances to infinity, mark all vertices as unvisited, and prepare the priority queue
  for (int i = 0; i < graph->num_vertices; i++) {
    distances[i] = INFINITY; // Initial distance set to "infinity"
    visited[i] = false; // Initially, no vertex is visited
    priorityQueue[i] = i; // Vertex indices are directly used for initial priority queue setup
  }

  // Set the distance from the source to itself as 0
  distances[from] = 0;

  // Sort the priority queue based on the initial distances
  updatePriorityQueue(priorityQueue, distances, graph->num_vertices);

  // Iterate over all vertices to find the shortest paths
  for (int i = 0; i < graph->num_vertices; i++) {
    // Extract the closest unvisited vertex
    int u = extMin(priorityQueue, visited, distances, graph->num_vertices);

    if (u == -1) break; // Stop if there are no unvisited vertices left

    // Relax edges adjacent to the current vertex
    for (dnode_t *temp = graph->adj_list[u]; temp != NULL; temp = temp->next) {
      int v = temp->destination;
      // If the edge leads to an unvisited vertex and offers a shorter path, update the distance
      if (!visited[v] && distances[u] + temp->weight < distances[v]) {
	distances[v] = distances[u] + temp->weight;
	// Re-sort the priority queue to reflect the updated distances
	updatePriorityQueue(priorityQueue, distances, graph->num_vertices);
      }
    }
  }

  // Clean up allocated memory
  free(visited);
  free(priorityQueue);
  return distances; // Return the array of shortest distances
}
