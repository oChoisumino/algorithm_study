#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

typedef int Node;

typedef struct _ArrayStack {
    int capacity;
    int top;
    Node *node;
}ArrayStack;

void create_stack(ArrayStack **stack, int capacity);

void destroy_stack(ArrayStack *stack);

void push_stack(ArrayStack *stack, Node node);

Node pop_stack(ArrayStack *stack);

#endif //STACK_ARRAY_H
