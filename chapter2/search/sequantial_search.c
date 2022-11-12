#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sequantial_search.h"

void create_node(Node *node)
{
    node = (Node *)malloc(sizeof(Node));
    node->next = NULL;
}

void destroy_node(Node *node)
{
    free(node);
}

void append_tail(Node **head, Node *node)
{
    if (*head == NULL) {
        *head = node;
    } else {
        Node *find_node = *head;
        while(find_node->next_node != NULL) {
            find_node = find_node->next_node;
        }
        find_node->next_node = node;
    }
}

Node *sequantial_search(Node *head, int target)
{
    Node *current = head;

    while(current->next != NULL) {
        if (current->data == target) {
            break;
        } else {
            current = current->next;
        }
    }
    return current;
}

Node move_to_front(Node **head, int target)
{
    Node *current = *head;
    Node *previous = NULL;

    while(current != NULL) {
        if (current->data == target) {
            break;
        } else {
            previous = current;
            current = current->next;
        }
    }
    if (previous != NULL) { // NULL인 경우 이미 맨 앞에 위치함
        previous->next = current->next;

        current->next = *head;
        *head = current;
    }
}
/* vitamin Quiz : int 배열에 사용 가능한 전진 이동 순차 탐색 */
void move_to_front_array(int arr[], int target)
{
    int index = 0;
    int num = sizeof(arr) / sizeof(arr[0]);

    for(int i = 0; i < num; i++) {
        if (arr[i] == target) {
            index = i;
            break;
        }
    }
    memcpy(&arr[1], &arr[0], sizeof(arr[0]) * index);
    arr[0] = target;
}

Node *transpose(Node **head, int target)
{
    Node *current = *head;
    Node *previous = NULL;
    Node *pprevious = NULL;

    while(current != NULL) {
        if (current->data == target) {
            break;
        } else {
            pprevious = previous;
            previous = current;
            current = current->next;
        }
    }
    if (previous != NULL) {
        if (pprevious == NULL) {
            *head = current;
        } else {
            pprevious->next = current;

        }
        previous->next = current->next;
        current->next = previous;
    } 
    return current;
}

/* vitamin Quiz : tranpose 함수의 배열 버전*/
void tranpose_array (int arr[], int target)
{
    int len = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < len; i++) {
        if (arr[i] == target) {
            if (i != 0) {
                int num = arr[i-1];
                arr[i-1] = arr[i];
                arr[i] = num;
            }
            break;
        }
    }
}
