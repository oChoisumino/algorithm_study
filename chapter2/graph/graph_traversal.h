#ifndef GRAPH_TRAVERSAL_H
#define GRAPH_TRAVERSAL_H

#include "graph.h"

typedef struct _Node {
    Vertex *data;
    struct _Node *next_node;
} Node;

typedef struct _LinkedQueue {
    Node *front;
    Node *rear;
    int count;
} LinkedQueue;

void create_queue(LinkedQueue **queue);

void enqueue(LinkedQueue *queue, Node * new_node);

Node *dequeue(LinkedQueue *queue);

void destroy_queue(LinkedQueue *queue);
Node *create_node(Vertex *new_data);

void destroy_node(Node *node);

#endif // GRAPH_TRAVERSAL_H
