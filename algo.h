//
// Created by eitan on 1/6/23.
//
#include <stdbool.h>
#include <limits.h>

// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
int minDistance(int dist[], bool sptSet[],int length);
// A utility function to print the constructed distance
// array

// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
int dijkstra(int *graph, int src, int dest, int length) ;