#ifndef MIN_SPANNING_TREE_H
#define MIN_SPANNING_TREE_H

#define MAX_WEIGHT (10000)
enum {
    NOT_VISITED = 0,
    VISITED = 1,
};

typedef struct _Graph {
    int vertex_cnt;
    struct _Vertex *vertices;
} Graph;

typedef struct _Edge {
    int weight;

    struct _Edge *next;
    struct _Vertex *from;
    struct _Vertex *target;
} Edge;

typedef struct _Vertex {
    char data;
    int visited;
    int index;

    struct _Vertex *next;
    struct _Edge *adjacency_list;
} Vertex;

typedef struct _PQNode {
    int priority;
    Vertex *data;
} PQNode;

typedef struct _PriorityQueue {
    PQNode *node;
    int capacity;
    int used_size;
} PriorityQueue;


Graph *create_graph();
void destroy_graph(Graph *graph);

Vertex *create_vertex(char data);

void destroy_vertex(Vertex *vertex);

Edge *create_edge(Vertex *from, Vertex *target, int weight);

void destroy_edge(Edge *edge);
void add_vertex(Graph *graph, Vertex *vertex);
void add_edge(Vertex *vertex, Edge *edge);
PriorityQueue *create_queue(int size);
void destroy_queue(PriorityQueue *queue);

int get_parent_index(int index);
int get_left_child_index(int index);

void swap(PQNode *a, PQNode *b);
void pq_enqueue(PriorityQueue *queue, PQNode *new_node);

void pq_dequeue(PriorityQueue *queue, PQNode *root);



void prim(Graph *graph, Vertex *start_vertex, Graph *min_spanning_tree);
void kruskal(Graph *graph, Graph *min_spanning_tree);

void print_graph (Graph *graph);

#endif //MIN_SPANNING_TREE_H
