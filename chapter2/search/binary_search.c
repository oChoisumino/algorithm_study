#include <stdio.h>
#include "binary_search.h"

int binary_search(int dataset[], int size, int target)
{
    int left, right, mid;

    left = 0;
    right = size - 1;

    while (left <= right) {
        mid = (left + right) / 2;
        if (dataset[mid] == target) {
            return mid;
        } else if (dataset[mid] < target) { 
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}