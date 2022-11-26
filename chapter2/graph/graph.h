#ifndef GRAPH_H
#define GRAPH_H

enum {
    NOT_VISITED = 0,
    VISITED = 1,
};

typedef struct _Vertex {
    char data;
    int visited;
    int index;

    struct _Vertex *next;
    struct _Edge *adjacency_list;
} Vertex;

typedef struct _Edge {
    int weight;

    struct _Edge *next;
    struct _Vertex *from;
    struct _Vertex *target;
} Edge;


typedef struct _Graph {
    int vertex_cnt;
    struct _Vertex *vertices;
} Graph;

Graph *create_graph(void);
void destroy_graph(Graph *graph);
Vertex *create_vertex(char data);
void destroy_vertex(Vertex *Vertex);
Edge *create_edge(Vertex *from, Vertex *target, int weight);

void destroy_edge(Edge *edge);
void add_vertex(Graph *graph, Vertex *vertex);

void add_edge(Vertex *vertex, Edge *edge);
void print_graph (Graph *graph);

#endif // GRAPH_H