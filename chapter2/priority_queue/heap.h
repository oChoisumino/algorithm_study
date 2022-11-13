#ifndef HEAP_H
#define HEAP_H

typedef struct _HeapNode {
    int data;
} HeapNode;

typedef struct _HEAP {
    HeapNode *node;
    int capacity;
    int used_size;
} HEAP;

HEAP *create_heap(int size);

void destroy_heap(HEAP *heap);

int get_parent_index(int index);
int get_left_child_index(int index);
void swap(HeapNode *a, HeapNode *b);
void heap_insert(HEAP *heap, int data);

void heap_delete_min(HEAP *heap, HeapNode *root);
void print_all(HEAP *heap);

#endif // HEAP_H