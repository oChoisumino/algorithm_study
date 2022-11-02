#include <stdio.h>
#include <stdlib.h>
#include "stack_linked_list.h"


Node *create_node(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));

    node->data = data;
    node->next_node = NULL;

    return node;
}

void destroy_node(Node *node)
{
    free(node);
}

void push_node(LLStack *stack, Node *node)
{
    if(stack->list == NULL) {
        stack->list = node;
    } else {
        stack->top->next_node = node; 
    }
    stack->top = node;
}

Node *pop_node(LLStack *stack)
{
    Node *top = stack->top;

    if ((stack->list == NULL) || (stack->top == NULL)) {
        return NULL;
    }

    if (stack->list == stack->top) {
        stack->list = NULL;
        stack->top = NULL;
    } else {
        Node *node = stack->list;
        
        while(node->next_node != top) {
            node = node->next_node;
        }
        node->next_node = NULL;
        stack->top = node;
    }
    return top;
} 

void create_stack(LLStack **stack)
{
    *stack = (LLStack *)malloc(sizeof(LLStack));
    (*stack)->list = NULL;
    (*stack)->top = NULL;
}

void destroy_stack(LLStack *stack)
{
    Node *node = NULL;
    while((stack->list != NULL) && (stack->top != NULL)) {
        node = pop_node(stack);
        destroy_node(node);
    }
    free(stack);
}

int main(void)
{
    LLStack *stack = NULL;
    Node *node = NULL;

    create_stack(&stack);
    while(1) {
        int num = 0;
        printf("1: push, 2: pop, 3: print, other: quit \n");
        printf("number : ");
        scanf("%d", &num);

        if (num == 1) {
            int data;

            printf("Data value : ");
            scanf("%d", &data);

            node = create_node(data);
            push_node(stack, node);
        } else if (num == 2) {
            node = pop_node(stack);
            destroy_node(node);
        } else if (num == 3) {
            node = stack->list;
            while(node != NULL) {
                printf("node : %d \n", node->data);
                node = node->next_node;
            }
            printf("top : %d \n", stack->top->data);
        } else {
            printf("end \n");
            break;
        }
    }
    destroy_stack(stack);
    
    return 0;
}