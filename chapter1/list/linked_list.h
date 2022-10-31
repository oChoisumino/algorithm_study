#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct _Node {
    int data;
    struct _Node *next_node;
}Node ;

Node *create_node(int data);

void destroy_node(Node *node);

void append_tail(Node **head, Node *node);
void append_node(Node **node, Node *new_node);
Node *find_node_with_data(Node *head, int data);

Node *find_node_with_index(Node *head, int index);

void delete_tail(Node **head);

void delete_node(Node **head, Node *node);

#endif //LINKED_LIST_H