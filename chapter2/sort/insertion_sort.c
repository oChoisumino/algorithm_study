#include <stdio.h>
#include <string.h>

void insertion_sort(int dataset[], int length) 
{
    for (int i = 1; i < length; i++) {
        int data = 0;
        if (dataset[i-1] < dataset[i]) {
            continue;
        }
        data = dataset[i];

        for (int j = 0; j < i; j++) {
            if (data < dataset[j]) {
                memcpy(&dataset[j+1], &dataset[j], sizeof(int)*(i-j));
                dataset[j] = data;
                break;
            }
        }
    }    
}

int main(void)
{
    int dataset[7] = {6,4,8,9,1,2};
    int num = sizeof(dataset) / sizeof(dataset[0]);
    insertion_sort(dataset, num);

    for (int i = 0; i < num; i++) {
        printf("%d ", dataset[i]);
    }
    return 0;
}