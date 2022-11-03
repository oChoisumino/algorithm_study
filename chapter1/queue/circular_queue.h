#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

typedef int ElementType;

typedef struct _Node {
    ElementType Data;
} Node;

typedef struct _CircularQueue {
    int capacity;
    int front;
    int rear;
    Node *nodes;
} CircularQueue;

void create_queue(CircularQueue **queue, int capacity);

void destroy_queue(CircularQueue *queue);

void enqueue(CircularQueue *queue, ElementType data);

ElementType dequeue(CircularQueue *queue);

int is_empty(CircularQueue *queue);

int is_full(CircularQueue *queue);
#endif //CIRCULAR_QUEUE_H
