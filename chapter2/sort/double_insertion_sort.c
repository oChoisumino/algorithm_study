#include <stdio.h>
#include <stdlib.h>
#include "double_insertion_sort.h"

DL_Node *create_node(int data)
{
    DL_Node *node = (DL_Node *)malloc(sizeof(DL_Node));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
}

void destroy_node(DL_Node *node)
{
    free(node);
}

void append_after(DL_Node **node, DL_Node *new_node)
{
    if (*node == NULL) {
        *node = new_node;
    } else {
        if ((*node)->next != NULL) {
            (*node)->next->prev = new_node;
        }
        new_node->next = (*node)->next;
        (*node)->next = new_node;
        new_node->prev = *node;
    }
}

void append_prev(DL_Node **node, DL_Node *new_node)
{
    int is_head = 1;
    if (*node == NULL) {
        *node = new_node;
    } else {
        if ((*node)->prev != NULL) {
            (*node)->prev->next = new_node;
            is_head = 0;
        }

        new_node->prev = (*node)->prev;
        (*node)->prev = new_node;
        new_node->next = *node;
        if (is_head == 1) {
            *node = new_node;
        }
    }
}

int count_node(DL_Node *head) 
{
    int cnt = 0;
    DL_Node *node = head;

    while (node != NULL) {
        node = node->next;
        cnt++;
    }
    return cnt;
}

DL_Node *get_node_by_index(DL_Node *head, int index)
{
    DL_Node *node = head;

    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    return node;
}

void delete_node(DL_Node **head, DL_Node *node)
{
    if (*head != NULL && node != NULL) {
        DL_Node *find = *head;
        while (find->next != node) {
            find = find->next;
        }
        find->next = node->next;
        if (node->next != NULL) {
        }
        destroy_node(node);
    }
}

void insertion_sort(DL_Node **head, int length)
{
    for (int i = 1; i < length; i++) {
        DL_Node *left = get_node_by_index(*head, i-1);

        DL_Node *right = get_node_by_index(*head, i);
        int data = 0;
        if (left->data < right->data) {
            continue;
        }
        data = right->data;
        for (int j = 0; j < i; j++) {
            left = get_node_by_index(*head, j);
            if (data < left->data) {
                DL_Node *node = create_node(right->data);
                delete_node(head, right);
                if (left == *head) {
                    append_prev(head, node);
                } else {
                    append_prev(&left, node);
                }
                break;
            }
        }
    }
}

int main(void)
{
    int dataset[7] = {6,4,8,9,1,2,3};
    int num = sizeof(dataset) / sizeof(dataset[0]);
    DL_Node *head = NULL, *pos = NULL;
    DL_Node *node = NULL;
    
    for (int i = 0; i < num; i++) {
        node = create_node(dataset[i]);
        if (pos == NULL) {
            append_after(&head, node);
        }
        append_after(&pos, node);
        pos = node;
    }

    num = count_node(head);
    insertion_sort(&head, num);

    node = head;
    for (int i = 0; i < num; i++) {
        printf("%d ", node->data);
        node = node->next;
    }
    return 0;

}