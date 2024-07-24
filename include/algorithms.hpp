#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "graph.hpp"
#include "priority_queue.hpp"

int dijkstra(Graph* graph, int start);
int dijkstra(Matrix* matrix, int start);
int a_star(Graph* graph, int start, int goal);
int a_star(Matrix* matrix, int start, int goal);


#endif // ALGORITHMS_HPP
