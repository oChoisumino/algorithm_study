#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_case(int *num_list, int *lotto_number, int start, int depth, int count) {
    if (depth == 6) {
        for(int i = 0; i < depth; i++) {
            printf("%d ", lotto_number[i]);
        }
        printf("\n");
        return;
    }
    for (int i = start; i < count; i++) {
        lotto_number[depth] = num_list[i];
        print_case(num_list, lotto_number, i+1, depth+1, count);
    }

}

int main(void)
{
    while (1){
        int count = 0;
        int *num_list;
        int lotto_list[6] = {0};
        
        scanf("%d", &count);

        if (count < 6) {
            return 0;
        }
        if (count == 0) {
            return 0;
        }
        num_list = (int *) malloc(sizeof(int) * count);

        for (int i = 0; i < count; i++) {
            scanf(" %d", &num_list[i]);
        }

        print_case(&num_list[0], &lotto_list[0], 0, 0, count );

        free (num_list);
    }
    return 0;
}