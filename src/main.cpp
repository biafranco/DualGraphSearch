#include <iostream>
#include <cmath>

using namespace std;

typedef struct edge {
    int target_vertice;
    double weight;
    double heuristic;
    bool is_portal;
    struct edge *next_edge;
} Edge;

typedef struct vertice {
    int index;
    int x;
    int y;
    Edge *edges;
} Vertice;

// Graph using lists instead of matrix
typedef struct graph {
    int n_egdes;
    int n_vertices;
    int n_portals;
    double hero_energy;
    int portal_limit;
    Vertice *vertices;
    Vertice *end;
} Graph;

// Priority queue using lists instead of tree
typedef struct priority_queue_node {
    int vertice_index;
    double value;
    struct priority_queue_node* next;
} PriorityQueueNode;

typedef struct priority_queue {
    PriorityQueueNode* first_node;
} PriorityQueue;

PriorityQueueNode* createPriorityQueueNode(int vertice_index, double priority_value) {
    PriorityQueueNode* node = new PriorityQueueNode;
    node->vertice_index = vertice_index;
    node->value = priority_value;
    node->next = nullptr;
    return node;
}

PriorityQueue* createPriorityQueue() {
    PriorityQueue* priority_queue = new PriorityQueue;
    priority_queue->first_node = createPriorityQueueNode(-1, -1); // HEAD
    return priority_queue;
}

void destroyPriorityQueue(PriorityQueue* priority_queue) {
    while (priority_queue->first_node != nullptr) {
        PriorityQueueNode* node = priority_queue->first_node;
        priority_queue->first_node = node->next;
        delete node;
    }
    delete priority_queue;
}

void insertVerticePriorityQueue(PriorityQueue* priority_queue, int vertice_index, double priority_value) {
    PriorityQueueNode* new_node = createPriorityQueueNode(vertice_index, priority_value);
    PriorityQueueNode* head_node = priority_queue->first_node;

    if(head_node->next) {
        PriorityQueueNode* current_node = head_node->next;
        while(current_node->value < priority_value) {
            head_node = current_node;
            current_node = current_node->next;
        }
        head_node->next = new_node;
        new_node->next = current_node;
    } else {
        head_node->next = new_node;
    }
}

int removeVerticePriorityQueue(PriorityQueue* priority_queue) {
    PriorityQueueNode* head_node = priority_queue->first_node; 
    PriorityQueueNode* remove_node = head_node->next; 
    head_node->next = remove_node->next;
    int index = remove_node->vertice_index;
    delete remove_node;
    return index;
}

Vertice* createVertices(int n_vertices) {
    Vertice* vertices = new Vertice[n_vertices];
    for (int i = 0; i < n_vertices; i++) {
        vertices[i].index = i;
        vertices[i].edges = nullptr;
    }
    return vertices;
}

Graph* createGraph(int n_vertices, int n_paths, int n_portals)  {
    Graph* graph = new Graph;

    graph->n_egdes = n_paths;
    graph->n_vertices = n_vertices;
    graph->n_portals = n_portals;
    graph->vertices = createVertices(n_vertices);
    graph->end = &(graph->vertices[n_vertices - 1]);

    return graph;
}

double calculateWeight(graph* graph, int source_vertice, int target_vertice, bool is_portal) {
    if (is_portal) {
        return 0;
    }
    
    // Use euclidean distance as weight
    double delta_x = pow(graph->vertices[source_vertice].x - graph->vertices[target_vertice].x, 2);
    double delta_y = pow(graph->vertices[source_vertice].y - graph->vertices[target_vertice].y, 2);
    double euclidean_distance = sqrt(delta_x + delta_y);
    return euclidean_distance;
}

void createEdge(graph* graph, int source_vertice, int target_vertice, bool is_portal) {
    Edge* new_edge = new Edge;
    new_edge->target_vertice = target_vertice;
    new_edge->is_portal = is_portal;
    // Calculate weight
    new_edge->weight = calculateWeight(graph, source_vertice, target_vertice, is_portal);
    new_edge->heuristic = calculateWeight(graph, target_vertice, graph->end->index, false);
    // Change the graph to store the new edge
    new_edge->next_edge = graph->vertices[source_vertice].edges;
    graph->vertices[source_vertice].edges = new_edge;
}

void printGraph(Graph* graph) {
    cout << "[graph boundaries: v:" << graph->n_vertices << ", e:" << graph->n_egdes << ", p:" << graph->n_portals  << "]" << endl;
    cout << "[graph limits: he:" << graph->hero_energy << ", pl:" << graph->portal_limit  << "]" << endl;
    for (int i = 0; i < graph->n_vertices; i++) {
        Vertice vertice = graph->vertices[i];
        cout << "[i:" << vertice.index << " (x:" << vertice.x << ", y:" << vertice.y <<  ")" << "] \t-> ";

        Edge* edge = vertice.edges;
        while (edge) {
            cout << "(tv:" << edge->target_vertice << ": w:" << edge->weight << ", h:" << edge->heuristic << ", ip:" <<  edge->is_portal << ") ";
            edge = edge->next_edge;
        }
        cout << endl;
    }
}

void solve(int n_vertices, int n_paths, int n_portals) {
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

    printGraph(graph);
}

int main() {
    int n_vertices, n_paths, n_portals;

    while (cin >> n_vertices >> n_paths >> n_portals) {
        solve(n_vertices, n_paths, n_portals);
    }

    return 0;
}
