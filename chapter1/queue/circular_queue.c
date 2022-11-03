#include <stdio.h>
#include <stdlib.h>
#include "circular_queue.h"

void create_queue(CircularQueue **queue, int capacity)
{
    *queue = (CircularQueue *)malloc(sizeof(CircularQueue));
    (*queue)->nodes = (Node *)malloc(sizeof(Node)*(capacity+1));
    (*queue)->capacity = capacity;
    (*queue)->front = 0;
    (*queue)->rear = 0;
}

void destroy_queue(CircularQueue *queue)
{
    free(queue->nodes);
    free(queue);
}

void enqueue(CircularQueue *queue, ElementType data)
{
    int position = 0;
    if (queue->rear == queue->capacity) {
        position = queue->rear;
        queue->rear = 0;
    } else {
        position = queue->rear++;
    }
    queue->nodes[position].Data = data;
}

ElementType dequeue(CircularQueue *queue) 
{
    int position = 0;
    if (queue->capacity == queue->front) {
        position = queue->front;
        queue->front = 0;
    } else {
        position = queue->front++;
    }
    return queue->nodes[position].Data;
}

int is_empty(CircularQueue *queue)
{
    if(queue->front == queue->rear) {
        return 1;
    } else {
        return 0;
    }
}

int is_full(CircularQueue *queue)
{
    if (queue->front < queue->rear) {
        return ((queue->rear-queue->front) ==  queue->capacity);
    } else {
        return ((queue->rear+1) == queue->front);
    }
}
int main(void) 
{
    CircularQueue *queue = NULL;
    int size;
    int i = 0;
    printf("queue size : ");
    scanf("%d", &size);
    
    create_queue(&queue, size);
    while(1) {
        int num = 0;
        printf("1: enqueue, 2: dequeue, 3: print, other: quit \n");
        printf("number : ");
        scanf("%d", &num);

        if (num == 1) {
            enqueue(queue, i++);
            printf("enqueue capacity %d, front %d rear %d\n", queue->capacity, queue->front, queue->rear);
        } else if (num == 2){
            int data = dequeue(queue);
            printf("dequeue data %d capacity %d, front %d rear %d\n", data, queue->capacity, queue->front, queue->rear);
        } else {
            break;
        }
    }
    destroy_queue(queue);

}
