#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int cnt;
    int pos;
    struct _Node *next;
} Node;

typedef struct _LinkedQueue {
    Node *start;
    Node *end;
} LinkedQueue;

Node *create_node(int cnt, int pos)
{
    Node *node = (Node *) malloc(sizeof(Node));
    node->cnt = cnt;
    node->pos = pos;
    node->next = NULL;
    
    return node;
}

void destroy_node(Node *node)
{
    free(node);
}

LinkedQueue *create_queue(void)
{
    LinkedQueue *queue = (LinkedQueue *) malloc(sizeof(LinkedQueue));

    queue->start = NULL;
    queue->end = NULL;

    return queue;
}

void destroy_queue(LinkedQueue *queue)
{
    if (queue != NULL) {
        while (queue->start != NULL) {
            Node *node = queue->start->next;
            destroy_node(queue->start);
            queue->start = node;
        }
        free(queue);
    }
}

void enqueue(LinkedQueue *queue, Node *node)
{
    if (queue == NULL) {
        return;
    }
    if (queue->start == NULL) {
        queue->start = node;
        queue->end = node;
    } else {
        queue->end->next = node;
        queue->end = node;
    }
}

Node *dequeue(LinkedQueue *queue)
{
    Node *pop = queue->start;

    if (queue == NULL) {
        return NULL;
    }

    if (queue->start == NULL) {
        return NULL;
    }

    queue->start = queue->start->next;

    return pop;
}

int breadth_first_search(int current, int destination)
{
    LinkedQueue *queue = create_queue();
    Node *new_node = create_node(0, current);
    Node *pop = NULL;
    int new_cnt, new_pos;
    char is_visited[100001] = {0};

    if (current == destination) {
        return 0;
    }
    enqueue(queue, new_node);
    
    pop = dequeue(queue);
    while (pop != NULL) {
        new_cnt = pop->cnt + 1;
        // + 1
        new_pos = pop->pos + 1;
        if (new_pos == destination) {
            break;
        } else {
            if ((new_pos > 0) && (new_pos <= 100000)) {
                if (is_visited[new_pos] == 0) {
                    new_node = create_node(new_cnt, new_pos);
                    enqueue(queue, new_node);
                    is_visited[new_pos] = 1;
                }
                
            }
        }

        // -1
        new_pos = pop->pos - 1;
        if (new_pos == destination) {
            break;
        } else {
            if ((new_pos > 0) && (new_pos <= 100000)) {
                if (is_visited[new_pos] == 0) {
                    new_node = create_node(new_cnt, new_pos);
                    enqueue(queue, new_node);
                    is_visited[new_pos] = 1;
                }
                
            }
        }
        // * 2
        new_pos = pop->pos * 2;
        if (new_pos == destination) {
            break;
        } else {
            if ((new_pos > 0) && (new_pos <= 100000)) {
                if (is_visited[new_pos] == 0) {
                    new_node = create_node(new_cnt, new_pos);
                    enqueue(queue, new_node);
                    is_visited[new_pos] = 1;
                }
                
            }
        }
        destroy_node(pop);
        pop = dequeue(queue);
    }
    if (pop != NULL) {
       destroy_node(pop);
    }
    destroy_queue(queue);
    return new_cnt;
}


int main(void)
{
    int subin_pos, brother_pos;
    int cnt;

    scanf("%d %d", &subin_pos, &brother_pos);

    cnt = breadth_first_search(subin_pos, brother_pos);
    printf("%d\n", cnt);

    return 0;
}

