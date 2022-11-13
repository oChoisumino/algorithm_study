#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"


HEAP *create_heap(int size)
{
    HEAP *heap = (HEAP *) malloc(sizeof(HEAP));
    
    heap->capacity = size;
    heap->used_size = 0;
    heap->node = (HeapNode *) malloc(sizeof(HeapNode)*size);

    return heap;
}

void destroy_heap(HEAP *heap)
{
    free(heap->node);

    free(heap);
}

int get_parent_index(int index)
{
    return (index-1)/2;
}

int get_left_child_index(int index)
{
    return (2 * index + 1);
}

void swap(HeapNode *a, HeapNode *b)
{
    HeapNode node = *a;
    *a = *b;
    *b = node;
}

void heap_insert(HEAP *heap, int data)
{
    int current_pos = heap->used_size;
    int parent_pos = get_parent_index(current_pos);

    if (heap->capacity == heap->used_size) {
        heap->capacity *= 2;
        heap->node = (HeapNode *)realloc(heap->node, sizeof(HeapNode) * heap->capacity);
    }
    
    heap->node[current_pos].data = data;
    if (current_pos != 0) {  
        while (heap->node[current_pos].data < heap->node[parent_pos].data) {
            swap(&heap->node[current_pos], &heap->node[parent_pos]);
            current_pos = parent_pos;
            parent_pos = get_parent_index(current_pos);
        }
    }
    heap->used_size++;
}

void heap_delete_min(HEAP *heap, HeapNode *root)
{
    int parent_pos = 0, left_pos = 0, right_pos = 0;

    memcpy(root, &heap->node[0], sizeof(HeapNode));
    memset(&heap->node[0], 0, sizeof(HeapNode));
    swap(&heap->node[0],&heap->node[heap->used_size-1]);
    heap->used_size--;

    while (1) {
        int comp_pos = 0;
        left_pos = get_left_child_index(parent_pos);
        right_pos = left_pos+1;

        if (left_pos >= heap->used_size) {
            break;
        }
        if (right_pos >= heap->used_size) {
            comp_pos = left_pos;
        } else {
            if (heap->node[left_pos].data < heap->node[right_pos].data) {
                comp_pos = left_pos;
            } else {
                comp_pos = right_pos;
            }
        }
        
        if (heap->node[comp_pos].data < heap->node[parent_pos].data) {
            swap(&heap->node[comp_pos], &heap->node[parent_pos]);
            parent_pos = comp_pos;
        } else {
            break;
        }
    }
    if (heap->used_size < (heap->capacity / 2)) {
        heap->node = (HeapNode *) realloc(heap->node, sizeof(HeapNode) * heap->capacity / 2);
        heap->capacity = heap->capacity / 2;
    }
}

void print_all(HEAP *heap) 
{
    for (int i = 0; i < heap->used_size; i++) {
        printf("%d ", heap->node[i].data);
    }
}

int main(void)
{
    HEAP *heap = create_heap(3);

    HeapNode min_node;

    heap_insert(heap, 12);
    heap_insert(heap, 87);
    heap_insert(heap, 111);
    heap_insert(heap, 34);
    heap_insert(heap, 16);
    heap_insert(heap, 75);

    print_all(heap);
    printf("\n");

    heap_delete_min(heap, &min_node);
    print_all(heap);
    printf("\n");

    heap_delete_min(heap, &min_node);
    print_all(heap);
    printf("\n");

    heap_delete_min(heap, &min_node);
    print_all(heap);
    printf("\n");

    heap_delete_min(heap, &min_node);
    print_all(heap);
    printf("\n");

    heap_delete_min(heap, &min_node);
    print_all(heap);
    printf("\n");

    heap_delete_min(heap, &min_node);
    print_all(heap);
    printf("\n");

    destroy_heap(heap);
    return 0;
}