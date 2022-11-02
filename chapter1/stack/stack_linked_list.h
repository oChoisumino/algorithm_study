#ifndef STACK_LINKED_LIST_H
#define STACK_LINKED_LIST_H

typedef struct _Node {
    int data;
    struct _Node *next_node;
} Node;

typedef struct _LinkedListStack {
    Node *list;
    Node *top;
} LLStack;


Node *create_node(int data);
void destroy_node(Node *node);

void push_node(LLStack *stack, Node *node);
Node *pop_node(LLStack *stack);

void create_stack(LLStack **stack);
void destroy_stack(LLStack *stack);

#endif //STACK_LINKED_LIST_H
