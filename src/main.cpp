#include <iostream>
#include "graph.hpp"
#include "priority_queue.hpp"
#include "algorithms.hpp"

using namespace std;

void solveList(int n_vertices, int n_paths, int n_portals) {
    int source_vertice, target_vertice;

    Graph* graph = createGraph(n_vertices, n_paths, n_portals);

    for (int i = 0; i < n_vertices; i++) {
        cin >> graph->vertices[i].x >> graph->vertices[i].y;
    }

    for (int i = 0; i < n_paths; i++) {
        cin >> source_vertice >> target_vertice;
        createEdge(graph, source_vertice, target_vertice, false);
    }

    for (int i = 0; i < n_portals; i++) {
        cin >> source_vertice >> target_vertice;
        createEdge(graph, source_vertice, target_vertice, true);
    }

    cin >> graph->hero_energy >> graph->portal_limit >> target_vertice;

    int dijkstra_returned = dijkstra(graph, 0);
    cout << dijkstra_returned << " ";

    int star_returned = a_star(graph, 0, n_vertices - 1);
    cout << star_returned << endl;
}

void solveMatrix(int n_vertices, int n_paths, int n_portals) {
    int source_vertice, target_vertice;

    Matrix* matrix = createMatrix(n_vertices, n_paths, n_portals);

    for (int i = 0; i < matrix->n_vertices; i++) {
        cin >> matrix->vertices[i].x >> matrix->vertices[i].y;
        matrix->vertices[i].index = i;
    }

    for (int i = 0; i < n_paths; i++) {
        int u, v;
        cin >> u >> v; 
        matrix->matrix_adj[u][v] = calculateWeight(matrix, u, v);
    }

    for (int i = 0; i < n_portals; i++) {
        int u, v;
        cin >> u >> v;
        matrix->matrix_adj[u][v] = -1;
    }

    cin >> matrix->hero_energy >> matrix->portal_limit >> target_vertice;

    int dijkstra_returned = dijkstra(matrix, 0);
    cout << dijkstra_returned << " ";

    int star_returned = a_star(matrix, 0, n_vertices - 1);
    cout << star_returned << endl;

    //printMatrix(matrix);
}

int main() {
    int n_vertices, n_paths, n_portals;

    while (cin >> n_vertices >> n_paths >> n_portals) {
        solveList(n_vertices, n_paths, n_portals);
        solveMatrix(n_vertices, n_paths, n_portals);
    }

    return 0;
}
