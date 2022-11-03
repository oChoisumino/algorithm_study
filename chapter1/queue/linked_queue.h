#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H


#include <stdio.h>
#include <stdlib.h>
#include "linked_queue.h"

typedef struct _Node {
    char *data;
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
Node *create_node(char *new_data);

void destroy_node(Node *node);

int is_empty(LinkedQueue *queue);
#endif //LINKED_QUEUE_H
