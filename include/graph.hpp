#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <cmath>

using namespace std;

typedef struct edge {
    int target_vertice;
    double weight;
    bool is_portal;
    struct edge *next_edge;
} Edge;

typedef struct vertice {
    int index;
    double x;
    double y;

    // property don't used by matrices
    Edge *edges;
} Vertice;

typedef struct graph {
    int n_edges;
    int n_vertices;
    int n_portals;
    double hero_energy;
    int portal_limit;
    Vertice *vertices;
    Vertice *end;
} Graph;

typedef struct matrix {
    int n_edges;
    int n_vertices;
    int n_portals;
    double hero_energy;
    int portal_limit;
    double **matrix_adj;

    Vertice *vertices;
    Vertice *end;
} Matrix;


Vertice* createVertices(int n_vertices);

Graph* createGraph(int n_vertices, int n_paths, int n_portals);
Matrix* createMatrix(int n_vertices, int n_paths, int n_portals);

void createEdge(Graph* graph, int source_vertice, int target_vertice, bool is_portal);
void createEdge(Matrix* matrix, int source_vertice, int target_vertice, bool is_portal);

double calculateWeight(Graph* graph, int source_vertice, int target_vertice);
double calculateWeight(Matrix* matrix, int source_vertice, int target_vertice);

void printGraph(Graph* graph);
void printMatrix(Matrix* matrix);


#endif // GRAPH_HPP
