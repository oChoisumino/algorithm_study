#include <stdio.h>
#include "../../chapter1/stack/stack_linked_list.h"
#include "quick_sort.h"

// main이 중복되어 stack_linked_list.c, quick_sort.c에서 main 주석 처리 후 실행해야 함
int main(void)
{
    LLStack *stack = NULL; 
    Node *lnode = NULL, *rnode;
    int dataset[7] = {6,4,8,9,1,2,0};
    int left = 0, right = sizeof(dataset) / sizeof(dataset[0]);

    create_stack(&stack);

    lnode = create_node(left);
    rnode = create_node(right);

    while ((rnode != NULL) && (lnode != NULL)) {
        int index = partition(dataset, left, right);

        if (index != left) {
            lnode = create_node(left);
            rnode = create_node(index-1);
            push_node(stack, lnode);
            push_node(stack, rnode);

            lnode = create_node(left);
            rnode = create_node(index-1);
            push_node(stack, lnode);
            push_node(stack, rnode);
        }

        rnode = pop_node(stack);
        lnode = pop_node(stack);
    }
    for (int i = 0; i < 7; i++) {
        printf("%d ", dataset[i]);
    }
}
