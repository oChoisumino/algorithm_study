#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node{
    int weight;
    int value;
} Node;

typedef struct _PQ{
    Node *node;
    int capacity;
    int used_size;
} PriorityQueue;

PriorityQueue *create_queue(int size)
{
    PriorityQueue *queue = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    queue->capacity = size;
    queue->used_size = 0;
    queue->node = (Node *) malloc(sizeof(Node) * size);
    
    return queue;
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

void swap(Node *node1, Node *node2)
{
    Node node = *node1;
    *node1 = *node2;
    *node2 = node;
}

void enqueue(PriorityQueue *queue, int weight, int value)
{
    int current_pos = queue->used_size;
    int parent_pos = get_parent_index(current_pos);

/*    if (queue->capacity == queue->used_size) {
        queue->capacity = queue->capacity * 2;
        queue->node = (Node *) realloc(queue->node, sizeof(Node) * queue->capacity);
    }*/

    queue->node[current_pos].value = value;
    queue->node[current_pos].weight = weight;

    while (queue->node[current_pos].value > queue->node[parent_pos].value) {
        swap(&queue->node[current_pos], &queue->node[parent_pos]);
        current_pos = parent_pos;
        parent_pos = get_parent_index(current_pos);
    }

    queue->used_size++;
}

void dequeue(PriorityQueue *queue, Node *root)
{
    int parent_pos = 0, left_pos = 0, right_pos = 0;

    memcpy(root, &queue->node[0], sizeof(Node));
    if (queue->used_size <= 0) {
        return;
    }
    swap(&queue->node[0], &queue->node[queue->used_size-1]);
    queue->used_size--;

    while (1) {
        int comp_val = 0;

        left_pos = get_left_child_index(parent_pos);
        right_pos = left_pos + 1;

        if (left_pos >= queue->used_size) {
            break;
        }

        if (right_pos >= queue->used_size) {
            comp_val = left_pos;
        } else {
            if (queue->node[left_pos].value < queue->node[right_pos].value) {
                comp_val = right_pos;
            } else {
                comp_val = left_pos;
            }
        }
        if (queue->node[parent_pos].value < queue->node[comp_val].value) {
            swap(&queue->node[parent_pos], &queue->node[comp_val]);

            parent_pos = comp_val;
        } else {
            break;
        }
    }

 /*   if (queue->used_size < queue->capacity / 2) {
        queue->capacity = queue->capacity / 2;
        queue->node = (Node *) realloc(queue->node, sizeof(Node) * queue->capacity);
    }*/
}


int main()
{
    int jewel_num, bag_num, max_weight;
    int jewel_val = 0, jewel_weight = 0;
    long long total_value = 0;
    PriorityQueue *queue = create_queue(300000);
    Node node = {0};
    
    scanf("%d %d", &jewel_num, &bag_num);
    for (int i = 0; i < jewel_num; i++) {
        scanf("%d %d", &jewel_weight, &jewel_val);
        enqueue(queue, jewel_weight, jewel_val);
    }

    scanf("%d", &max_weight);

    for (int i = 0; i < bag_num; i++) {
        dequeue(queue, &node);
        if (node.weight > max_weight) {
            i--;
        } else {
            total_value = node.value + total_value;
        }
    }
    
    printf("%lld \n", total_value);
    destroy_queue(queue);

    return 0;
}