#include <stdio.h>
#include "bubble_sort.h"

void bubble_sort(int data[], int num)
{
    for (int i = 0; i < (num-1); i++) {
        for (int j = 0; j < (num-1-i); j++) {
            if (data[j] > data[j+1]) {
                int save = data[j];
                data[j] = data[j+1];
                data[j+1] = save;
            }
        }
    }
}

/* vitamin quiz : 정렬 되어 있는 경우에는 루프를 취소하고 빠져나오도록 알고리즘 개선 */
void bubble_sort_improve(int data[], int num) 
{
    for (int i = 0; i < (num-1); i++) {
        int need_sort = 0;
        for (int j = 0; j < (num-1-i); j++) {
            if (data[j] > data[j+1]) {
                int save = data[j];
                data[j] = data[j+1];
                data[j+1] = save;
                need_sort = 1;
            } 
        }

        if (need_sort == 0) {
            break;
        }
    }
}

int main(void)
{
    int dataset[7] = {6,4,8,9,1,2};
    int num = sizeof(dataset) / sizeof(dataset[0]);
    bubble_sort(dataset, num);

    for (int i = 0; i < num; i++) {
        printf("%d ", dataset[i]);
    }
    return 0;
}