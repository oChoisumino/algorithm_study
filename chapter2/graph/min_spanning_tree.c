#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disjoint_set.h"
#include "min_spanning_tree.h"

Graph *create_graph()
{
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    graph->vertex_cnt = 0;
    graph->vertices = NULL;

    return graph;
}

void destroy_graph(Graph *graph)
{
    while (graph->vertices != NULL) {
        destroy_vertex(graph->vertices);
        graph->vertices = graph->vertices->next;
    }
    free(graph);
}

Vertex *create_vertex(char data)
{
    Vertex *vertex = (Vertex *) malloc(sizeof(Vertex));

    vertex->data = data;
    vertex->index = -1;
    vertex->adjacency_list = NULL;
    vertex->next = NULL;
    vertex->visited = NOT_VISITED;

    return vertex;
}

void destroy_vertex(Vertex *vertex)
{
    while(vertex->adjacency_list != NULL) {
        Edge *edge = vertex->adjacency_list->next;
        destroy_edge(vertex->adjacency_list);
        vertex->adjacency_list = edge;
    }
    free(vertex);
}

Edge *create_edge(Vertex *from, Vertex *target, int weight)
{
    Edge *edge = (Edge *) malloc(sizeof(Edge));

    edge->from = from;
    edge->target = target;
    edge->weight = weight;
    edge->next = NULL;

    return edge;
}

void destroy_edge(Edge *edge)
{
    free(edge);
}

void add_vertex(Graph *graph, Vertex *vertex)
{
    Vertex *list = graph->vertices;
    if (list == NULL) {
        graph->vertices = vertex;
        vertex->index = 0;
    } else {
        while(list->next != NULL) {
            list = list->next;
        }
        list->next = vertex;
        vertex->index = list->index + 1;
    }
    graph->vertex_cnt++;
}

void add_edge(Vertex *vertex, Edge *edge)
{
    Edge *list = vertex->adjacency_list;
    if (list == NULL) {
        vertex->adjacency_list = edge;
    } else {
        while (list->next != NULL) {
            list = list->next;
        }
        list->next = edge;
    }
}

PriorityQueue *create_queue(int size)
{
    PriorityQueue *queue = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    queue->capacity = size;
    queue->used_size = 0;
    queue->node = (PQNode *) malloc(sizeof(PQNode) * size);
    return queue;
}

void destroy_queue(PriorityQueue *queue)
{
    free(queue->node);
    free(queue);
}

int get_parent_index(int index)
{
    return (index - 1) / 2;
}

int get_left_child_index(int index)
{
    return (index * 2 + 1);
}

void swap(PQNode *a, PQNode *b)
{
    PQNode val = *a;
    *a = *b;
    *b = val;
}

void pq_enqueue(PriorityQueue *queue, PQNode *new_node)
{
    int current_pos = queue->used_size;
    int parent_pos = get_parent_index(current_pos);

    printf("enqueue %c \n", new_node->data->data);
    if (queue->capacity <= queue->used_size) {
        queue->capacity = queue->capacity * 2;
        queue->node = (PQNode *) realloc(queue->node, sizeof(PQNode) * queue->capacity);
    }
    memcpy(&queue->node[current_pos], new_node, sizeof(PQNode));
    while (queue->node[current_pos].priority < queue->node[parent_pos].priority) {
        swap(&queue->node[current_pos], &queue->node[parent_pos]);
        current_pos = parent_pos;
        parent_pos = get_parent_index(current_pos);
    }
    queue->used_size++;
}

void pq_dequeue(PriorityQueue *queue, PQNode *root)
{
    int parent_pos = 0, left_pos, right_pos;

    memcpy(root, &queue->node[0], sizeof(PQNode));
    swap(&queue->node[0], &queue->node[queue->used_size-1]);

    printf("dequeue %c index %d \n", root->data->data, root->data->index);
    queue->used_size--;

    while(1) {
        int comp_val;

        left_pos = get_left_child_index(parent_pos);
        right_pos = left_pos + 1;

        if (left_pos >= queue->used_size) {
            break;
        } 
        if (right_pos >= queue->used_size) {
            comp_val = left_pos;
        } else {
            if (queue->node[left_pos].priority < queue->node[right_pos].priority) {
                comp_val = left_pos;
            } else {
                comp_val = right_pos;
            }
        }

        if (queue->node[comp_val].priority < queue->node[parent_pos].priority) {
            swap(&queue->node[comp_val], &queue->node[parent_pos]);
        } else {
            break;
        }
    }

    if (queue->used_size < queue->capacity / 2) {
        queue->capacity = queue->capacity / 2;
        queue->node = (PQNode *) realloc(queue->node, sizeof(PQNode) * queue->capacity);
    }
}



void prim(Graph *graph, Vertex *start_vertex, Graph *min_spanning_tree)
{
    int i = 0;

    PQNode start_node = {0, start_vertex};
    PriorityQueue *queue = create_queue(15);

    Vertex *current_vertex = NULL;
    Edge *current_edge = NULL;

    int *weights = (int *) malloc(sizeof(int) * graph->vertex_cnt);
    Vertex **mst_vertices = (Vertex **) malloc(sizeof(Vertex) * graph->vertex_cnt);
    Vertex **fringes = (Vertex **) malloc(sizeof(Vertex) * graph->vertex_cnt);
    Vertex **precedences = (Vertex **) malloc(sizeof(Vertex) * graph->vertex_cnt);

    current_vertex = graph->vertices;

    while(current_vertex != NULL) {
        Vertex *new_vertex = create_vertex(current_vertex->data);

        add_vertex(min_spanning_tree, new_vertex);

        fringes[i] = NULL;
        precedences[i] = NULL;
        mst_vertices[i] = new_vertex;
        weights[i] = MAX_WEIGHT;
        current_vertex = current_vertex->next;
        i++;
    }

    pq_enqueue(queue, &start_node);

    weights[start_vertex->index] = 0;

    while (queue->used_size != 0) {
        PQNode popped;

        pq_dequeue(queue, &popped);

        current_vertex = popped.data;

        fringes[current_vertex->index] = current_vertex;

        current_edge = current_vertex->adjacency_list;

        while (current_edge != NULL) {
            Vertex *target = current_edge->target;
            if ((fringes[target->index] == NULL) && (current_edge->weight < weights[target->index])) {
                PQNode new_node = {current_edge->weight, target};

                pq_enqueue(queue, &new_node);

                precedences[target->index] = current_edge->from;
                weights[target->index] = current_edge->weight;
            }
            current_edge = current_edge->next;
        }
    }
    for (i = 0; i < graph->vertex_cnt; i++) {
        int from_index, to_index;

        if (precedences[i] == NULL) {
            continue;
        }
        from_index = precedences[i]->index;
        to_index = i;

        add_edge(mst_vertices[from_index], create_edge(mst_vertices[from_index], mst_vertices[to_index], weights[i]));

        add_edge(mst_vertices[to_index], create_edge(mst_vertices[to_index], mst_vertices[from_index], weights[i]));
    }

    free(fringes);
    free(precedences);
    free(mst_vertices);
    free(weights);

    destroy_queue(queue);
}

void kruskal(Graph *graph, Graph *min_spanning_tree)
{
    int i = 0;
    Vertex *current_vertex = NULL;
    Vertex **mst_vertices = (Vertex **) malloc(sizeof(Vertex) * graph->vertex_cnt);

    DisjointSet **vertex_set = (DisjointSet **) malloc(sizeof(DisjointSet *) * graph->vertex_cnt);

    PriorityQueue *queue = create_queue(15);

    current_vertex = graph->vertices;

    while (current_vertex != NULL) {
        Edge *current_edge;

        vertex_set[i] = make_set((void *) current_vertex);

        mst_vertices[i] = create_vertex(current_vertex->data);

        add_vertex(min_spanning_tree, mst_vertices[i]);

        current_edge = current_vertex->adjacency_list;

        while (current_edge != NULL) {
            PQNode new_node = {current_edge->weight, (Vertex *)current_edge};

            pq_enqueue(queue, &new_node);

            current_edge = current_edge->next;
        }
        current_vertex = current_vertex->next;
        i++;
    }

    while (queue->used_size != 0) {
        Edge *current_edge;
        int from_index, to_index;
        PQNode popped;

        pq_dequeue(queue, &popped);
        current_edge = (Edge *) popped.data;

        from_index = current_edge->from->index;
        to_index = current_edge->target->index;

        if (find_root(vertex_set[from_index]) != find_root(vertex_set[to_index])) {
            add_edge(mst_vertices[from_index], create_edge(mst_vertices[from_index], mst_vertices[to_index], current_edge->weight));

            add_edge(mst_vertices[to_index], create_edge(mst_vertices[to_index], mst_vertices[from_index], current_edge->weight));
            
            union_set(vertex_set[from_index], vertex_set[to_index]);
        }
  }

    for (i = 0; i < graph->vertex_cnt; i++) {
        distroy_set(vertex_set[i]);
    }
    free(vertex_set);
    free(mst_vertices);
}

void dijkstra(Graph *graph, Vertex *start_vertex, Graph *shortest_path)
{
    int i = 0;

    PQNode start_node = {0, start_vertex};
    PriorityQueue *queue = create_queue(10);

    Vertex *current_vertex = NULL;
    Edge *current_edge = NULL;

    int *weights = (int *) malloc(sizeof(int) * graph->vertex_cnt);
    
    Vertex **shortest_path_vertices = (Vertex **) malloc(sizeof(PQNode) * graph->vertex_cnt);
    Vertex **Fringes = (Vertex **) malloc(sizeof(Vertex) * graph->vertex_cnt);
    Vertex **precedences = (Vertex **) malloc(sizeof(Vertex) * graph->vertex_cnt);

    current_vertex = graph->vertices;
    while (current_vertex != NULL) {
        Vertex *new_vertex = create_vertex(current_vertex->data);
        add_vertex(shortest_path, new_vertex);

        Fringes[i] = NULL;
        precedences[i] = NULL;
        shortest_path_vertices[i] = new_vertex;
        weights[i] = MAX_WEIGHT;
        current_vertex = current_vertex->next;

        i++;
    }
    
    pq_enqueue(queue, &start_node);

    weights[start_vertex->index] = 0;

    while (queue->used_size > 0) {
        PQNode popped;

        pq_dequeue(queue, &popped);
        current_vertex = popped.data;

        Fringes[current_vertex->index] = current_vertex;

        current_edge = current_vertex->adjacency_list;

        while (current_edge != NULL) {
            Vertex *target = current_edge->target;

            if ((Fringes[target->index] == NULL) && (weights[current_vertex->index] + current_edge->weight < weights[target->index])) {
                PQNode new_node = {current_edge->weight, target};

                pq_enqueue(queue, &new_node);

                precedences[target->index] = current_edge->from;
                weights[target->index] = weights[current_vertex->index] + current_edge->weight;
            }
            current_edge = current_edge->next;
        }
    }

    for (i = 0; i < graph->vertex_cnt; i++) {
        int from_index, to_index;

        if (precedences[i] == NULL) {
            continue;
        }

        from_index = precedences[i]->index;
        to_index = i;

        add_edge(shortest_path_vertices[from_index], create_edge(shortest_path_vertices[from_index], shortest_path_vertices[to_index], weights[i]));
    }

    free(Fringes);
    free(precedences);
    free(shortest_path_vertices);
    free(weights);

    destroy_queue(queue);
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

        printf("\n");

        vertex = vertex->next;
    }
    printf("\n");
}

int main(void)
{
    Graph *graph = create_graph();
    Graph *prim_mst = create_graph();
    Graph *kruskal_mst = create_graph();
    Graph *dijkstra_mst = create_graph();

    Vertex *A = create_vertex('A');
    Vertex *B = create_vertex('B');
    Vertex *C = create_vertex('C');
    Vertex *D = create_vertex('D');
    Vertex *E = create_vertex('E');
    Vertex *F = create_vertex('F');
    Vertex *G = create_vertex('G');
    Vertex *H = create_vertex('H');
    Vertex *I = create_vertex('I');

    add_vertex(graph, A);
    add_vertex(graph, B);
    add_vertex(graph, C);
    add_vertex(graph, D);
    add_vertex(graph, E);
    add_vertex(graph, F);
    add_vertex(graph, G);
    add_vertex(graph, H);
    add_vertex(graph, I);

    add_edge(A, create_edge(A, B, 35));
    add_edge(A, create_edge(A, E, 247));

    add_edge(B, create_edge(B, A, 35));
    add_edge(B, create_edge(B, C, 126));
    add_edge(B, create_edge(B, F, 150));

    add_edge(C, create_edge(C, B, 126));
    add_edge(C, create_edge(C, D, 117));
    add_edge(C, create_edge(C, F, 162));
    add_edge(C, create_edge(C, G, 220));

    add_edge(D, create_edge(D, C, 117));

    add_edge(E, create_edge(E, A, 247));
    add_edge(E, create_edge(E, F, 82));
    add_edge(E, create_edge(E, H, 98));

    add_edge(F, create_edge(F, B, 150));
    add_edge(F, create_edge(F, C, 162));
    add_edge(F, create_edge(F, E, 82));
    add_edge(F, create_edge(F, G, 154));
    add_edge(F, create_edge(F, H, 120));

    add_edge(G, create_edge(G, C, 220));
    add_edge(G, create_edge(G, F, 154));
    add_edge(G, create_edge(G, I, 106));

    add_edge(H, create_edge(H, E, 98));
    add_edge(H, create_edge(H, F, 120));

    add_edge(I, create_edge(I, G, 106));

    print_graph(graph);

    printf("Prim's Algorithm \n");
    prim(graph, B, prim_mst);
    print_graph(prim_mst);

    printf("Kruskal's Algorithm \n");
    kruskal(graph, kruskal_mst);
    print_graph(kruskal_mst);
    
    printf("dijkstra's Algorithm \n");
    dijkstra(graph, B, dijkstra_mst);
    print_graph(dijkstra_mst);

    destroy_graph(graph);
    destroy_graph(prim_mst);
    destroy_graph(kruskal_mst);
    return 0;
}
