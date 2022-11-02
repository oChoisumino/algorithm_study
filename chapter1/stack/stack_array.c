#include <stdio.h>
#include <stdlib.h>
#include "stack_array.h"
// 노드가 존재하는 위치는 배열의 인덱스로 알 수 있음

void create_stack(ArrayStack **stack, int capacity)
{
    *stack = (ArrayStack *)malloc(sizeof(ArrayStack));

    (*stack)->node = (Node *)malloc(sizeof(Node)*capacity);
    (*stack)->capacity = capacity;
    (*stack)->top = 0;
}

void destroy_stack(ArrayStack *stack)
{
    free(stack->node);
    free(stack);
}

void push_stack(ArrayStack *stack, Node node)
{
    if ((stack->top + 1) >= stack->capacity) {
        printf("failed to push stack");
    } else {
        stack->node[stack->top] = node;
        stack->top++;
    }
}

Node pop_stack(ArrayStack *stack)
{
    stack->top--;
    return stack->node[stack->top];
}

/*vitamin quiz : is_full 작성(스택 용량이 가득 차있는가)*/
int is_full(ArrayStack *stack) {
    if (stack->capacity == (stack->top-1)) {
        return 1;
    } else {
        return 0;
    }
}
int main(void)
{
    ArrayStack *stack = NULL;
    int size;
    printf("Stack size : ");
    scanf("%d", &size);
    
    create_stack(&stack, size);
    while(1) {
        int num = 0;
        printf("1: push, 2: pop, 3: print, other: quit \n");
        printf("number : ");
        scanf("%d", &num);

        if (num == 1) {
            Node data;
            printf("Data value : ");
            scanf("%d", &data);
            push_stack(stack, data);
        } else if (num == 2) {
            pop_stack(stack);
        }else if (num == 3) {
            for (int i = 0; i < stack->top; i++) {
                printf("%d\n", stack->node[i]); 
            }
        } else {
            printf("end \n");
            break;
        }
    }
    destroy_stack(stack);
}