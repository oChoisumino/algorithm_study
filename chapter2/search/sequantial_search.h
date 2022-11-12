#ifndef SEQUANTIAL_SEARCH_H
#define SEQUANTIAL_SEARCH_H

typedef struct _Node {
    int data;
    struct _Node *next;
}Node;

void create_node(Node *node);
void destroy_node(Node *node);
void append_tail(Node **head, Node *node);
Node *sequantial_search(Node *head, int target);

Node move_to_front(Node **head, int target);
void move_to_front_array(int arr[], int target);

Node *transpose(Node **head, int target);
void tranpose_array (int arr[], int target);

#endif