#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue.h"

PriorityQueue *create_queue(int size)
{
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));

    pq->capacity = size;
    pq->used_size = 0;
    pq->node = (PQNode *) malloc(sizeof(PQNode)*size);

    return pq;
}

void destroy_queue(PriorityQueue *queue)
{
    free(queue->node);
    free(queue);
}

int get_parent_index(int index)
{
    return ((index - 1) / 2);
}

int get_left_child_index(int index)
{
    return (2 * index + 1);
}

void swap(PQNode *a, PQNode *b)
{
    PQNode node = *a;
    *a = *b;
    *b = node;
}

void pq_enqueue(PriorityQueue *pq, PQNode *node)
{
    int current_pos = pq->used_size;
    int parent_pos = get_parent_index(current_pos);

    if (pq->capacity == pq->used_size) {
        pq->capacity *= 2;
        pq->node = (PQNode *) realloc(pq->node, sizeof(PQNode)*pq->capacity);
    }

    pq->node[current_pos].data = node->data;
    pq->node[current_pos].priority = node->priority;

    while(pq->node[parent_pos].priority > pq->node[current_pos].priority) {
        swap(&pq->node[parent_pos], &pq->node[current_pos]);
        current_pos = parent_pos;
        parent_pos = get_parent_index(current_pos);
    }
    pq->used_size++;
}

void pq_dequeue(PriorityQueue *pq, PQNode *root)
{
    int parent_pos = 0, left_pos = 0, right_pos = 0;

    memcpy(root, &pq->node[0], sizeof(PQNode));
    swap(&pq->node[0], &pq->node[pq->used_size-1]);

    pq->used_size--;

    while(1) {
        int comp_val = 0;
        
        left_pos = get_left_child_index(parent_pos);
        right_pos = left_pos + 1;

        if (left_pos >= pq->used_size) {
            break;
        }
        if (right_pos >= pq->used_size) {
            comp_val = left_pos;
        } else {
            if (pq->node[left_pos].priority < pq->node[right_pos].priority) {
                comp_val = left_pos;
            } else {
                comp_val = right_pos;
            }
        }
        
        if (pq->node[comp_val].priority < pq->node[parent_pos].priority) {
            swap(&pq->node[comp_val], &pq->node[parent_pos]);

            parent_pos = comp_val;
        } else {
            break;
        }
    }

    if (pq->used_size < (pq->capacity / 2)) {
        pq->capacity = pq->capacity / 2;
        pq->node = (PQNode *)realloc(pq->node, sizeof(PQNode) * pq->capacity);
    }
}
