#ifndef QUICK_SORT_H
#define QUICK_SORT_H

void swap(int *a, int *b);
int partition(int dataset[], int left, int right);
int quick_sort(int dataset[], int left, int right);

int compare_val(const void *data1, const void *data2);

#endif //QUICK_SORT_H