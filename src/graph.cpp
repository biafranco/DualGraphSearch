#include "graph.hpp"

Vertice* createVertices(int n_vertices) {
    Vertice* vertices = new Vertice[n_vertices];
    for (int i = 0; i < n_vertices; i++) {
        vertices[i].index = i;
        vertices[i].edges = nullptr;
    }
    return vertices;
}

Graph* createGraph(int n_vertices, int n_paths, int n_portals) {
    Graph* graph = new Graph;

    graph->n_edges = n_paths;
    graph->n_vertices = n_vertices;
    graph->n_portals = n_portals;
    graph->vertices = createVertices(n_vertices);
    graph->end = &(graph->vertices[n_vertices - 1]);

    return graph;
}

Matrix* createMatrix(int n_vertices, int n_paths, int n_portals) {
    Matrix* matrix = new Matrix;

    matrix->n_edges = n_paths;
    matrix->n_vertices = n_vertices;
    matrix->n_portals = n_portals;
    matrix->vertices = new Vertice[n_vertices];
    matrix->end = &(matrix->vertices[n_vertices - 1]);
    matrix->matrix_adj = new double*[n_vertices];

    for (int i = 0; i < n_vertices; i++) {
        matrix->matrix_adj[i] = new double[n_vertices];
        for (int j = 0; j < n_vertices; j++) {
            matrix->matrix_adj[i][j] = 0;
        }
    }

    return matrix;
}

double calculateWeight(Graph* graph, int source_vertice, int target_vertice) {
    double delta_x = pow(graph->vertices[source_vertice].x - graph->vertices[target_vertice].x, 2);
    double delta_y = pow(graph->vertices[source_vertice].y - graph->vertices[target_vertice].y, 2);
    double euclidean_distance = sqrt(delta_x + delta_y);
    return euclidean_distance;
}

double calculateWeight(Matrix* matrix, int source_vertice, int target_vertice) {
    double delta_x = pow(matrix->vertices[source_vertice].x - matrix->vertices[target_vertice].x, 2);
    double delta_y = pow(matrix->vertices[source_vertice].y - matrix->vertices[target_vertice].y, 2);
    double euclidean_distance = sqrt(delta_x + delta_y);
    return euclidean_distance;
}

void createEdge(Graph* graph, int source_vertice, int target_vertice, bool is_portal) {
    Edge* new_edge = new Edge;
    new_edge->target_vertice = target_vertice;
    new_edge->is_portal = is_portal;
    new_edge->weight = calculateWeight(graph, source_vertice, target_vertice);
    new_edge->next_edge = graph->vertices[source_vertice].edges;
    graph->vertices[source_vertice].edges = new_edge;
}


void printGraph(Graph* graph) {
    cout << "[graph boundaries: v:" << graph->n_vertices << ", e:" << graph->n_edges << ", p:" << graph->n_portals << "]" << endl;
    cout << "[graph limits: he:" << graph->hero_energy << ", pl:" << graph->portal_limit << "]" << endl;
    for (int i = 0; i < graph->n_vertices; i++) {
        Vertice vertice = graph->vertices[i];
        cout << "[i:" << vertice.index << " (x:" << vertice.x << ", y:" << vertice.y << ")] \t-> ";

        Edge* edge = vertice.edges;
        while (edge) {
            cout << "(tv:" << edge->target_vertice << ": w:" << edge->weight << ", ip:" << edge->is_portal << ") ";
            edge = edge->next_edge;
        }
        cout << endl;
    }
}

void printMatrix(Matrix* matrix) {
    cout << "[matrix boundaries: v:" << matrix->n_vertices << ", e:" << matrix->n_edges << ", p:" << matrix->n_portals << "]" << endl;
    cout << "[matrix limits: he:" << matrix->hero_energy << ", pl:" << matrix->portal_limit << "]" << endl;

    for (int i = 0; i < matrix->n_vertices; i++) {
        for (int j = 0; j < matrix->n_vertices; j++) {
            cout << matrix->matrix_adj[i][j] << " ";
        }
        cout << endl;
    }
}

