#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

typedef struct _Node {
    Vertex *vertex;
    struct _Node *next;
} Node;


Node *create_node(Vertex *vertex)
{
    Node *node = (Node *) malloc(sizeof(Node));
    node->next = NULL;
    node->vertex = vertex;
}

void insert_head(Node **list, Node **new_node)
{
    (*new_node)->next = *list;
    (*list) = *new_node;
}

void deep_first_search(Vertex *vertex, Node **list)
{
    Node *new_head = NULL;
    Edge *edge = NULL;

    vertex->visited = VISITED;

    edge = vertex->adjacency_list;

    while(edge != NULL) {
        if (edge->target != NULL && edge->target->visited == NOT_VISITED) {
            deep_first_search(edge->target, list);
        }
        edge = edge->next;
    }
    
    new_head = create_node(vertex);
    insert_head(list, &new_head);
}

void topological_sort(Vertex *vertex, Node **list)
{
    while(vertex != NULL && vertex->visited == NOT_VISITED) {
        deep_first_search(vertex, list);
        vertex = vertex->next;
    }
}

int main(void)
{
    Node *sorted_list = NULL;
    Node *current_node = NULL;

    Graph *graph = create_graph();

    Vertex *v1 = create_vertex('A');
    Vertex *v2 = create_vertex('B');
    Vertex *v3 = create_vertex('C');
    Vertex *v4 = create_vertex('D');
    Vertex *v5 = create_vertex('E');
    Vertex *v6 = create_vertex('F');
    Vertex *v7 = create_vertex('G');
    Vertex *v8 = create_vertex('H');

    add_vertex(graph, v1);
    add_vertex(graph, v2);
    add_vertex(graph, v3);
    add_vertex(graph, v4);
    add_vertex(graph, v5);
    add_vertex(graph, v6);
    add_vertex(graph, v7);
    add_vertex(graph, v8);

    add_edge(v1, create_edge(v1, v3, 0));
    add_edge(v1, create_edge(v1, v4, 0));

    add_edge(v2, create_edge(v2, v3, 0));
    add_edge(v2, create_edge(v2, v5, 0));

    add_edge(v3, create_edge(v3, v6, 0));

    add_edge(v4, create_edge(v4, v6, 0));
    add_edge(v4, create_edge(v4, v7, 0));

    add_edge(v5, create_edge(v5, v7, 0));

    add_edge(v6, create_edge(v6, v8, 0));

    add_edge(v7, create_edge(v7, v8, 0));

    topological_sort(graph->vertices, &sorted_list);
    current_node = sorted_list;
    while(current_node != NULL) {
        printf("%c ", current_node->vertex->data);
        current_node = current_node->next;
    }

    destroy_graph(graph);

    return 0;
}
