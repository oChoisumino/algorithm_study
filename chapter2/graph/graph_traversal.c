#include <stdio.h>
#include <stdlib.h>
#include "graph_traversal.h"

void create_queue(LinkedQueue **queue)
{
    *queue = (LinkedQueue *)malloc(sizeof(LinkedQueue));
    (*queue)->count = 0;
    (*queue)->front = NULL;
    (*queue)->rear = NULL;

}

void enqueue(LinkedQueue *queue, Node * new_node)
{
    if (queue->front == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next_node = new_node;
        queue->rear = new_node;
    }
    queue->count++;
}

Node *dequeue(LinkedQueue *queue)
{
    Node *node = queue->front;
    if (queue->front->next_node == NULL) {
        queue->front = NULL;
        queue->rear = NULL;
    } else {
        queue->front = queue->front->next_node;
    }
    queue->count--;
    return node;
}

void destroy_queue(LinkedQueue *queue)
{
    while(queue->front != NULL) {
        Node *node = dequeue(queue);
        destroy_node(node);
    }
    free(queue);
}
Node *create_node(Vertex *new_data)
{
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = new_data;
    node->next_node = NULL;
    return node;
}

void destroy_node(Node *node)
{
    destroy_vertex(node->data);
    free(node);
}


void deep_first_search(Vertex *vertex)
{
    Edge *edge = NULL;
    
    vertex->visited = VISITED;
    edge = vertex->adjacency_list;

    while (edge != NULL) {
        if ((edge->target != NULL) && (edge->target->visited == NOT_VISITED)) {
            deep_first_search(edge->target);
        }
        edge = edge->next;
    }
}

void breadth_first_search(Vertex *vertex, LinkedQueue *queue)
{
    Edge *edge = NULL;

    vertex->visited = VISITED;
    enqueue(queue, create_node(vertex));

    while (queue->front != NULL) {
        Node *popped = dequeue(queue);
        
        vertex = popped->data;
        edge = vertex->adjacency_list;

        while (edge != NULL) {
            vertex = edge->target;
            if ((vertex != NULL) && (vertex->visited == NOT_VISITED)) {
                vertex->visited = VISITED;
                enqueue(queue, create_node(edge->target));
            }
            edge = edge->next;
        }
    }
}


int main(void)
{
    Graph *graph = create_graph();
    int mode;

    Vertex *v1 = create_vertex('1');
    Vertex *v2 = create_vertex('2');
    Vertex *v3 = create_vertex('3');
    Vertex *v4 = create_vertex('4');
    Vertex *v5 = create_vertex('5');
    Vertex *v6 = create_vertex('6');
    Vertex *v7 = create_vertex('7');

    add_vertex(graph, v1);
    add_vertex(graph, v2);
    add_vertex(graph, v3);
    add_vertex(graph, v4);
    add_vertex(graph, v5);
    add_vertex(graph, v6);
    add_vertex(graph, v7);

    add_edge(v1, create_edge(v1, v2, 0));
    add_edge(v1, create_edge(v1, v3, 0));

    add_edge(v2, create_edge(v2, v4, 0));
    add_edge(v2, create_edge(v2, v5, 0));

    add_edge(v3, create_edge(v3, v4, 0));
    add_edge(v3, create_edge(v3, v6, 0));

    add_edge(v4, create_edge(v4, v5, 0));
    add_edge(v4, create_edge(v4, v7, 0));

    add_edge(v5, create_edge(v5, v7, 0));

    add_edge(v6, create_edge(v6, v7, 0));

    printf("enter traversal mode : 0 : DFS, 1: BFS \n");
    scanf("%d", &mode);

    if (mode == 0) {
        deep_first_search(graph->vertices);
    } else {
        LinkedQueue *queue = NULL;
        create_queue(&queue);

        breadth_first_search(v1, queue);

        destroy_queue(queue);
    }

    destroy_graph(graph);

    return 0;
}
