#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include "huffman.h"
typedef struct _PQNode {
    int priority;
    HuffmanNode *data;
    //char data[8];
} PQNode;

typedef struct _PriorityQueue {
    PQNode *node;
    int capacity;
    int used_size;
} PriorityQueue;


PriorityQueue *create_queue(int size);

void destroy_queue(PriorityQueue *queue);

int get_parent_index(int index);
int get_left_child_index(int index);

void swap(PQNode *a, PQNode *b);

void pq_enqueue(PriorityQueue *pq, PQNode *node);

void pq_dequeue(PriorityQueue *pq, PQNode *root);

void print_all(PriorityQueue *pq);
#endif // PRIORITY_QUEUE_H