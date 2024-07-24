#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

typedef struct priority_queue_node {
    int vertice_index;
    double value;
    struct priority_queue_node* next;
} PriorityQueueNode;

typedef struct priority_queue {
    PriorityQueueNode* first_node;
} PriorityQueue;

PriorityQueueNode* createPriorityQueueNode(int vertice_index, double priority_value);
PriorityQueue* createPriorityQueue();
void destroyPriorityQueue(PriorityQueue* priority_queue);
void insertVerticePriorityQueue(PriorityQueue* priority_queue, int vertice_index, double priority_value);
int removeVerticePriorityQueue(PriorityQueue* priority_queue);
bool isEmptyPriorityQueue(PriorityQueue* priority_queue);

#endif // PRIORITY_QUEUE_HPP
