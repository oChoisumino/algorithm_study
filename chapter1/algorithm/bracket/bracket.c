#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bracket.h"


Node *create_node(char data) 
{
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = data;
    node->next_node = NULL;

    return node;
}

void destroy_node(Node *node)
{
    free(node);
}

void create_stack(LinkedStack **stack)
{
    *stack = (LinkedStack *) malloc(sizeof(LinkedStack));
    (*stack)->head = NULL;
    (*stack)->top = NULL;
}

void destroy_stack(LinkedStack *stack)
{
    Node *node = NULL;

    while((stack->head != NULL) && (stack->top != NULL)) {
        node = pop_node(stack);
        destroy_node(node);
    }
    free(stack);
}

void push_node(LinkedStack *stack, Node *node)
{
    if (stack->head == NULL || stack->top == NULL) {
        stack->head = node;
        stack->top = node;
    } else {
        stack->top->next_node = node;        
    }
    stack->top = node;
}

Node *pop_node(LinkedStack *stack) 
{
    Node *pop_node = stack->top;

    if (stack->top == NULL || stack->head == NULL) {
        return NULL;
    }

    if (stack->top == stack->head) {
        stack->head = NULL;
        stack->top = NULL;
    } else {
        Node *node = stack->head;
        while(node->next_node != stack->top) {
            node = node->next_node;
        }
        node->next_node = NULL;
        stack->top = node;
    }
    return pop_node;
}
int is_start_correct (char str)
{
    return ((str == '(') || (str == '['));
}

int stack_capacity(LinkedStack *stack)
{
    Node *node = stack->head;
    int cnt = 0;
    if (node != NULL) {
        node = node->next_node;
        cnt++;
    }

    return cnt;
}

int is_num(char c) 
{
    int num = c - '0';
    if ((0 <= num) && (num <= 9)) {
        return 1;
    } else {
        return 0;
    }
}

int main(void)
{
    LinkedStack *stack = NULL;
    char bracket[30];
    int result = 0, str_len = 0;
    int i = 0;
    int number = 0;
    Node *new_node = NULL, *pop = NULL;

    scanf("%s", &bracket[0]);
    create_stack(&stack);
    if (is_start_correct(bracket[0])) {
        str_len = strlen(&bracket[0]);
    }

    while (i < str_len) {
        if ((bracket[i] == '(') || (bracket[i] == '[')) {
            new_node = create_node(bracket[i]);
            push_node(stack, new_node);
        } else if (bracket[i] == ')') {
            pop = pop_node(stack);

            if (is_num(pop->data)) { //pop한 데이터가 숫자인 경우
                number = pop->data - '0';
                destroy_node(pop);
                pop = pop_node(stack);

                if (pop->data == '(') { // 정상의 경우
                    number = number*2;
                    new_node = create_node((char)(number + '0'));
                    push_node(stack, new_node);
                } else if (is_num(pop->data)) { // 숫자 숫자인경우 +연산
                    while(is_num(pop->data)) {
                        number = number + pop->data - '0';
                        destroy_node(pop);
                        pop = pop_node(stack);
                    }

                    if ((pop != NULL) && (pop->data == '(')) {
                        destroy_node(pop);
                        new_node = create_node((char)(number*2)+ '0');
                        push_node(stack, new_node); 
                    } else {
                        result = -1;
                        break;                    }
                } else { // 정상이지 않은 경우
                    result = -1;
                    break;
                }
            } else if (pop->data == '(') {// pop한 데이터가 문자열인 경우
                new_node = create_node('2');
                push_node(stack, new_node);
            } else {
                result = -1;
                break;
            }
        } else if (bracket[i] == ']') {
            pop = pop_node(stack);

            if (is_num(pop->data)) { //pop한 데이터가 숫자인 경우
                number = pop->data - '0';
                destroy_node(pop);
                pop = pop_node(stack);

                if (pop->data == '[') { // 정상의 경우
                    number = number*3;
                    new_node = create_node((char)(number + '0'));
                    push_node(stack, new_node);
                } else if (is_num(pop->data)) { // 숫자 숫자인경우 +연산
                    while(is_num(pop->data)) {
                        number = number + pop->data - '0';
                        destroy_node(pop);
                        pop = pop_node(stack);
                    }

                    if ((pop != NULL) && (pop->data == '[')) {
                        destroy_node(pop);
                        new_node = create_node((char)(number*3)+ '0');
                        push_node(stack, new_node); 
                    } else {
                        result = -1;
                        break;
                    }
                } else { // 정상이지 않은 경우
                    result = -1;
                   break;
                }
            } else if (pop->data == '[') {// pop한 데이터가 문자열인 경우
                new_node = create_node('3');
                push_node(stack, new_node);
            } else {
                result = -1;
                break;
            }
        } else {
            result = -1;
            break;
        }
        i++;
    }

    pop = pop_node(stack);
    if (result == -1) {
        result = 0;
         while(pop != NULL) {
            destroy_node(pop);
            pop = pop_node(stack);
        }
   } else {
        while(pop != NULL) {
            result = result + (int)(pop->data - '0');
            destroy_node(pop);
            pop = pop_node(stack);
        }
    }
    printf("%d \n", result);

    destroy_stack;
    return result;
}