#include "algorithms.hpp"

int dijkstra(Graph* graph, int start) {
    double* distances = new double[graph->n_vertices];
    bool* visited = new bool[graph->n_vertices];
    int* portals_used = new int[graph->n_vertices];
    double* energy_remaining = new double[graph->n_vertices];

    for (int i = 0; i < graph->n_vertices; ++i) {
        distances[i] = numeric_limits<double>::infinity();
        visited[i] = false;
        portals_used[i] = 0;
        energy_remaining[i] = graph->hero_energy;
    }

    distances[start] = 0;

    PriorityQueue* pq = createPriorityQueue();
    insertVerticePriorityQueue(pq, start, 0);

    while (!isEmptyPriorityQueue(pq)) {
        int current = removeVerticePriorityQueue(pq);

        if (visited[current]) continue;
        visited[current] = true;

        Edge* edge = graph->vertices[current].edges;
        while (edge != nullptr) {
            int neighbor = edge->target_vertice;
            double weight = edge->weight;
            int new_portals_used = portals_used[current] + (edge->is_portal ? 1 : 0);
            double new_energy_remaining = energy_remaining[current] - (edge->is_portal ? 0 : weight);

            if (new_portals_used <= graph->portal_limit && new_energy_remaining >= 0) {
                if (!visited[neighbor] && distances[current] + weight < distances[neighbor]) {
                    distances[neighbor] = distances[current] + weight;
                    portals_used[neighbor] = new_portals_used;
                    energy_remaining[neighbor] = new_energy_remaining;
                    insertVerticePriorityQueue(pq, neighbor, distances[neighbor]);
                }
            }
            edge = edge->next_edge;
        }
    }

    int result = (distances[graph->n_vertices - 1] != numeric_limits<double>::infinity() && energy_remaining[graph->n_vertices - 1] >= 0) ? 1 : 0;

    delete[] distances;
    delete[] visited;
    delete[] portals_used;
    delete[] energy_remaining;
    destroyPriorityQueue(pq);

    return result;
}

int dijkstra(Matrix* matrix, int start) {
    double* distances = new double[matrix->n_vertices];
    bool* visited = new bool[matrix->n_vertices];
    int* portals_used = new int[matrix->n_vertices];
    double* energy_remaining = new double[matrix->n_vertices];

    for (int i = 0; i < matrix->n_vertices; ++i) {
        distances[i] = numeric_limits<double>::infinity();
        visited[i] = false;
        portals_used[i] = 0;
        energy_remaining[i] = matrix->hero_energy;
    }

    distances[start] = 0;

    PriorityQueue* pq = createPriorityQueue();
    insertVerticePriorityQueue(pq, start, 0);

    while (!isEmptyPriorityQueue(pq)) {
        int current = removeVerticePriorityQueue(pq);

        if (visited[current]) continue;
        visited[current] = true;

        for (int i = 0; i < matrix->n_vertices; i++) {
            double weight = matrix->matrix_adj[current][i];

            if (weight == 0) continue;

            int new_portals_used = portals_used[current] + (weight == -1 ? 1 : 0);
            int neighbor = i;
            double new_energy_remaining = energy_remaining[current] - (weight == -1 ? 0 : weight);

            if (new_portals_used <= matrix->portal_limit && new_energy_remaining >= 0) {
                if (!visited[neighbor] && distances[current] + weight < distances[neighbor]) {
                    distances[neighbor] = distances[current] + weight;
                    portals_used[neighbor] = new_portals_used;
                    energy_remaining[neighbor] = new_energy_remaining;
                    insertVerticePriorityQueue(pq, neighbor, distances[neighbor]);
         
                }
            }
        }
    }

    int result = (distances[matrix->n_vertices - 1] != numeric_limits<double>::infinity() && energy_remaining[matrix->n_vertices - 1] >= 0) ? 1 : 0;

    delete[] distances;
    delete[] visited;
    delete[] portals_used;
    delete[] energy_remaining;
    destroyPriorityQueue(pq);

    return result;
}

int a_star(Graph* graph, int start, int goal) {
    double* g_costs = new double[graph->n_vertices];
    double* f_costs = new double[graph->n_vertices];
    bool* visited = new bool[graph->n_vertices];
    int* portals_used = new int[graph->n_vertices];

    for (int i = 0; i < graph->n_vertices; ++i) {
        g_costs[i] = numeric_limits<double>::infinity();
        f_costs[i] = numeric_limits<double>::infinity();
        visited[i] = false;
        portals_used[i] = 0;
    }

    g_costs[start] = 0;
    f_costs[start] = calculateWeight(graph, start, goal);

    PriorityQueue* pq = createPriorityQueue();
    insertVerticePriorityQueue(pq, start, f_costs[start]);

    while (!isEmptyPriorityQueue(pq)) {
        int current = removeVerticePriorityQueue(pq);
        if (current == goal) {
            break;
        }

        visited[current] = true;

        Edge* edge = graph->vertices[current].edges;
        while (edge != nullptr) {
            int neighbor = edge->target_vertice;
            double tentative_g_cost = g_costs[current] + edge->weight;
            int new_portals_used = portals_used[current] + (edge->is_portal ? 1 : 0);

            if (tentative_g_cost <= graph->hero_energy && new_portals_used <= graph->portal_limit) {
                if (!visited[neighbor] && tentative_g_cost < g_costs[neighbor]) {
                    g_costs[neighbor] = tentative_g_cost;
                    f_costs[neighbor] = tentative_g_cost + calculateWeight(graph, neighbor, goal);
                    portals_used[neighbor] = new_portals_used;
                    insertVerticePriorityQueue(pq, neighbor, f_costs[neighbor]);
                }
            }
            edge = edge->next_edge;
        }
    }

    int result = (g_costs[goal] != numeric_limits<double>::infinity());

    delete[] g_costs;
    delete[] f_costs;
    delete[] visited;
    delete[] portals_used;
    destroyPriorityQueue(pq);

    return result;
}

int a_star(Matrix* matrix, int start, int goal) {
    double* g_costs = new double[matrix->n_vertices];
    double* f_costs = new double[matrix->n_vertices];
    bool* visited = new bool[matrix->n_vertices];
    int* portals_used = new int[matrix->n_vertices];

    for (int i = 0; i < matrix->n_vertices; ++i) {
        g_costs[i] = numeric_limits<double>::infinity();
        f_costs[i] = numeric_limits<double>::infinity();
        visited[i] = false;
        portals_used[i] = 0;
    }

    g_costs[start] = 0;
    f_costs[start] = calculateWeight(matrix, start, goal);

    PriorityQueue* pq = createPriorityQueue();
    insertVerticePriorityQueue(pq, start, f_costs[start]);

    while (!isEmptyPriorityQueue(pq)) {
        int current = removeVerticePriorityQueue(pq);

        if (current == goal) break;
        visited[current] = true;

        for (int i = 0; i < matrix->n_vertices; i++) {
            double weight = matrix->matrix_adj[current][i];
            if (weight == 0) continue;

            int new_portals_used = portals_used[current] + (weight == -1 ? 1 : 0);
            int neighbor = i;
            double tentative_g_cost = g_costs[current] + weight;

            if (tentative_g_cost <= matrix->hero_energy && new_portals_used <= matrix->portal_limit) {
                if (!visited[neighbor] && tentative_g_cost < g_costs[neighbor]) {
                    g_costs[neighbor] = tentative_g_cost;
                    f_costs[neighbor] = tentative_g_cost + calculateWeight(matrix, neighbor, goal);
                    portals_used[neighbor] = new_portals_used;
                    insertVerticePriorityQueue(pq, neighbor, f_costs[neighbor]);
                }
            }
        }
    }

    int result = (g_costs[goal] != numeric_limits<double>::infinity());

    delete[] g_costs;
    delete[] f_costs;
    delete[] visited;
    delete[] portals_used;
    destroyPriorityQueue(pq);

    return result;
}