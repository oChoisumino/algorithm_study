#include <stdio.h>
#include <stdlib.h>
#include "quick_sort.h"

void swap(int *a, int *b)
{
    int val = *a;
    *a = *b;
    *b = val;
}

int find_index(int dataset[], int left, int right)
{
    // 중간 값 확인
    int center_index = (left + right) / 2;

    if ((dataset[left] > dataset[right]) && (dataset[right] > dataset[center_index])) {
        return right;
    } else if ((dataset[left] > dataset[center_index]) && (dataset[center_index] > dataset[right])) {
        return center_index;
    } else if ((dataset[center_index] > dataset[left]) && (dataset[left] > dataset[right])) {
        return left;
    } else if ((dataset[center_index] > dataset[right]) && (dataset[right] > dataset[left])) {
        return right;
    } else if ((dataset[right] > dataset[center_index]) && (dataset[center_index] > dataset[left])) {
        return center_index;
    } else {
        return left;
    }
}
int partition_med(int dataset[], int left, int right)
{
    int first = left;
    int median_index = find_index(dataset, left, right);
    int pivot = dataset[median_index];
    left++;

    while (left < right) {
        while (dataset[left] <= pivot) {
            left++;
            if (left >= right) {
                break;
            }
        }
        while (dataset[right] >= pivot) {
            right--;
            if (right <= left) {
                break;
            }
        }

        if (left > right) {
            break;
        }
        swap(&dataset[left], &dataset[right]);
    }
    swap(&dataset[first], &dataset[right]);
    return right;

}

int partition(int dataset[], int left, int right)
{
    int first = left;
    int pivot = dataset[left];
    left++;

    while (left < right) {
        while (dataset[left] <= pivot) {
            left++;
            if (left >= right) {
                break;
            }
        }
        while (dataset[right] >= pivot) {
            right--;
            if (right <= left) {
                break;
            }
        }

        if (left > right) {
            break;
        }
        swap(&dataset[left], &dataset[right]);
    }
    swap(&dataset[first], &dataset[right]);
    return right;

}

int quick_sort(int dataset[], int left, int right)
{
    if (left < right)
    {
        int index = partition(dataset, left, right);

        quick_sort(dataset, left, index-1);
        quick_sort(dataset, index+1, right);
    }
}

int compare_val(const void *data1, const void *data2)
{
    int *val1 = (int *) data1;
    int *val2 = (int *) data2;

    if (*val1 > *val2) {
        return 1;
    } else if (*val1 == *val2) {
        return 0;
    } else {
        return -1;
    }
}

int main(void)
{ 
    int dataset[7] = {6,4,8,9,1,2,0};
    int std_dataset[7] = {6,4,8,9,1,2,0};

    int num = sizeof(dataset) / sizeof(dataset[0]);
    int std_num = sizeof(std_dataset) / sizeof(std_dataset[0]);

    quick_sort(dataset, 0, num-1);

    qsort((void *)std_dataset, std_num, sizeof(std_dataset[0]), compare_val);

    for (int i = 0; i < num; i++) {
        printf("%d ", dataset[i]);
    }
    printf("\n");
    for (int i = 0; i < std_num; i++) {
        printf("%d ", std_dataset[i]);
    }
    return 0;
}