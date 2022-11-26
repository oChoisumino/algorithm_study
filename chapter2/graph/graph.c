#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


Graph *create_graph(void)
{
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    graph->vertices = NULL;
    graph->vertex_cnt = 0;

    return graph;
}

void destroy_graph(Graph *graph)
{
    while(graph->vertices != NULL) {
        Vertex *vertex = graph->vertices->next;
        destroy_vertex(graph->vertices);
        graph->vertices = vertex;
    }
    free(graph);
}

Vertex *create_vertex(char data)
{
    Vertex *vertex = (Vertex *) malloc(sizeof(Vertex));
    vertex->data = data;
    vertex->next = NULL;
    vertex->adjacency_list = NULL;
    vertex->visited = NOT_VISITED;
    vertex->index = -1;

    return vertex;
}

void destroy_vertex(Vertex *Vertex)
{
    while(Vertex->adjacency_list != NULL) {
        Edge *edge = Vertex->adjacency_list->next;
        destroy_edge(Vertex->adjacency_list);
        Vertex->adjacency_list = edge;
    }
    free(Vertex);
}

Edge *create_edge(Vertex *from, Vertex *target, int weight)
{
    Edge *edge = (Edge *) malloc(sizeof(Edge));

    edge->from = from;
    edge->target = target;
    edge->next = NULL;
    edge->weight = weight;

    return edge;
}

void destroy_edge(Edge *edge)
{
    free(edge);
}

void add_vertex(Graph *graph, Vertex *vertex) // 정점 추가
{
    if (graph->vertices == NULL) {
        graph->vertices = vertex;
    } else {
        Vertex *vertex_next = graph->vertices;
        while (vertex_next->next != NULL) {
            vertex_next = vertex_next->next;
        }
        vertex_next->next = vertex;
    }
    graph->vertex_cnt++;
}

void add_edge(Vertex *vertex, Edge *edge)
{
    if (vertex->adjacency_list == NULL) {
        vertex->adjacency_list = edge;
    } else {
        Edge *edge_next = vertex->adjacency_list;
        while (edge_next->next != NULL) {
            edge_next = edge_next->next;
        }
        edge_next->next = edge;
    }
}

void print_graph (Graph *graph)
{
    Vertex *vertex = graph->vertices;
    Edge *edge = NULL;

    if (vertex == NULL) {
        return;
    }

    while (vertex != NULL) {
        edge = vertex->adjacency_list;
        printf("%c : ", vertex->data);

        if (edge == NULL) {
            vertex = vertex->next;
            printf("\n");
            continue;
        }

        while(edge != NULL) {
            printf("%c(%d) ", edge->target->data, edge->weight);
            edge = edge->next;
        }
        vertex = vertex->next;
        printf("\n");
    }
    printf("\n");
}
/*
int main(void)
{
    Graph *graph = create_graph();

    Vertex *v1 = create_vertex('1');
    Vertex *v2 = create_vertex('2');
    Vertex *v3 = create_vertex('3');
    Vertex *v4 = create_vertex('4');
    Vertex *v5 = create_vertex('5');

    add_vertex(graph, v1);
    add_vertex(graph, v2);
    add_vertex(graph, v3);
    add_vertex(graph, v4);
    add_vertex(graph, v5);

    add_edge(v1, create_edge(v1, v2, 0));
    add_edge(v1, create_edge(v1, v3, 0));
    add_edge(v1, create_edge(v1, v4, 0));
    add_edge(v1, create_edge(v1, v5, 0));

    add_edge(v2, create_edge(v2, v1, 0));
    add_edge(v2, create_edge(v2, v3, 0));
    add_edge(v2, create_edge(v2, v5, 0));

    add_edge(v3, create_edge(v3, v1, 0));
    add_edge(v3, create_edge(v3, v2, 0));

    add_edge(v4, create_edge(v4, v1, 0));
    add_edge(v4, create_edge(v4, v5, 0));

    add_edge(v5, create_edge(v5, v1, 0));
    add_edge(v5, create_edge(v5, v2, 0));
    add_edge(v5, create_edge(v5, v4, 0));

    print_graph(graph);

    destroy_graph(graph);

    return 0;
}*/
