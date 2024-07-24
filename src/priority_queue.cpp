#include "priority_queue.hpp"

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
            if (current_node == nullptr) {
                break;
            }
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

bool isEmptyPriorityQueue(PriorityQueue* priority_queue) {
    return priority_queue->first_node->next == nullptr;
}
