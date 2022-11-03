#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_queue.h"


void create_queue(LinkedQueue **queue)
{
    (*queue) = (LinkedQueue *)malloc(sizeof(LinkedQueue));
    (*queue)->front = NULL;
    (*queue)->rear = NULL;
    (*queue)->count = 0;
}

void enqueue(LinkedQueue *queue, Node * new_node)
{
    if (queue->front == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
        queue->count++;
    } else {
        queue->rear->next_node = new_node;
        queue->rear = new_node;
        queue->count++;
    }
}

Node *dequeue(LinkedQueue *queue) 
{
    Node *node = queue->front;

    if (queue->front->next_node == NULL) {
        queue->front = NULL;
        queue->rear = NULL;
    } else {
        queue->front = node->next_node;
    }
    queue->count--;
    
    return node;
}

void destroy_queue(LinkedQueue *queue)
{
    while (is_empty(queue)) {
        Node *popped = dequeue(queue);

        destroy_node(popped);
    }
    free(queue);
}

Node *create_node(char *new_data)
{
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = (char *)malloc(strlen(new_data)+1);
    node->next_node = NULL;

    strcpy(node->data, new_data);
    return node;
}

void destroy_node(Node *node)
{
    free(node->data);
    free(node);
}

int is_empty(LinkedQueue *queue)
{
    if(queue->front == NULL)
        return 1;
    else 
        return 0;
}

int main(void)
{
    LinkedQueue *queue = NULL;
    int i = 0;
    
    create_queue(&queue);
    while(1) {
        int num = 0;
        printf("1: enqueue, 2: dequeue1, other: quit \n");
        printf("number : ");
        scanf("%d", &num);

        if (num == 1) {
            char str[16] = {0};
            Node *node = NULL;

            scanf("%s", &str);

            node = create_node(str);
            enqueue(queue, node);
            printf("front %s rear %s\n", queue->front->data, queue->rear->data);
        } else if (num == 2){
            Node *node = dequeue(queue);
            printf("dequeue data %s\n", node->data);
        } else {
            break;
        }
    }
    destroy_queue(queue);
}