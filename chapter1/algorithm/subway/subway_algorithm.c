#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subway_algorithm.h"

typedef enum {
    TYPE_BN = 0,
    TYPE_BP = 1,
    TYPE_CP = 2,
    TYPE_CN = 3,
    TYPE_NUM = 4
} CONSTRUCT_TYPE_e;

Node *create_node(int data)
{
    Node * new_node = (Node *)malloc(sizeof(Node));

    new_node->data = data;
    new_node->prev_node = NULL;
    new_node->next_node = NULL;

    return new_node;
}

void destroy_node(Node *node)
{
    free(node);
}

void append_tail(Node **head, Node *new_node)
{
    if (*head == NULL) {
        *head = new_node;
        new_node->next_node = *head;
        new_node->prev_node = *head;
    } else {
        Node *node = *head;
        while(node->next_node != *head) {
            node = node->next_node;
        }
        node->next_node = new_node;
        new_node->next_node = *head;
        (*head)->prev_node = new_node;
        new_node->prev_node = node;
    }
}

void append_after(Node *list, Node *new_node)
{
        Node *node = list;
        if (node->next_node != NULL) {
            (node->next_node)->prev_node = new_node;
        }
        new_node->next_node = node->next_node;
        node->next_node = new_node;
        new_node->prev_node = node;
}

void append_prev(Node *list, Node *new_node)
{
        Node *node = list;
        if (node->prev_node != NULL) {
            (node->prev_node)->next_node = new_node;
        }
        new_node->next_node = node;
        new_node->prev_node = node->prev_node;
        node->prev_node = new_node;
}

Node *find_node_with_data(Node *head, int data)
{
    Node *node = head;

    if (node == NULL) {
        printf("none of nodes exist");
    } else {
        while(node != NULL) {
            if (node->data == data) {
                break;
            }
            node = node->next_node;
        }
        if (node == NULL) {
            printf("invalid data value");
        }
    }
    return node;
}

Node *find_node_with_index(Node *head, int index)
{
    Node *node = head;
    int count = index;
    
    for(int i = 1; i < index; i++) {
        if (node != NULL) {
            node = node->next_node;
        }
    }

    if (node == NULL) {
        printf("invalid data value");
    }
    return node;
}

void delete_tail(Node **head)
{
    if (*head != NULL) {
        Node *tail = *head;
        Node *find = NULL;
        while(tail->next_node != NULL) {
            find = tail;
            tail = tail->next_node;
        }
        find->next_node = NULL;
        destroy_node(tail);
    }
}

int delete_node(Node **head, Node *node)
{
    int data = node->data;
    if (head == NULL) {
        printf("none of nodes exist in linked list \n");
    } else {
        Node *find = *head;
        Node *next_node = NULL;
        while(find != NULL) {
            if (find->next_node == node) {
                break;
            }
            find = find->next_node;
        }
        find->next_node = node->next_node;
        (node->next_node)->prev_node = find;

        destroy_node(node);
    }
    return data;
}
void print_all(Node *head)
{
    Node *node = head;
    printf("print_all \n");

    while(node->next_node != NULL) {
        printf("%d \n", node->data);
        node = node->next_node;
    }
}

int main(void)
{
    int num = 0;
    Node *head = NULL;
    int current_station = 0, construct_num = 0;
    int *station_data = NULL; 
    int *data = NULL;

    scanf("%d %d", &current_station, &construct_num);

    data = (int *)malloc(sizeof(int)*current_station);
    for (int i = 0; i < current_station; i++) {
        if (i == current_station-1) {
            scanf("%d", &data[i]);
        } else {
            scanf("%d ", &data[i]);
        }
    }

    for (int i = 0; i < current_station; i++) {
        Node *curr_node = create_node(data[i]);

        append_tail(&head, curr_node);
    }
    
    for (int i = 0; i < construct_num; i++) {
        char type_input[3] = {0};
        scanf("%s", &type_input[0]);
        if (strcmp(type_input, "BN") == 0) {
            int unique_num, new_unique_num;
            Node *find_node = NULL, *new_node = NULL;
            scanf(" %d %d", &unique_num, &new_unique_num);

            new_node = create_node(new_unique_num);
            find_node = find_node_with_data(head, unique_num);

            append_after(find_node, new_node);
            printf("%d \n", (new_node->next_node)->data);
        } else if (strcmp(type_input, "BP") == 0) {
            int unique_num, new_unique_num;
            Node *find_node = NULL, *new_node = NULL;
            scanf(" %d %d", &unique_num, &new_unique_num);

            new_node = create_node(new_unique_num);
            find_node = find_node_with_data(head, unique_num);

            append_prev(find_node, new_node);
            printf("%d \n", (new_node->prev_node)->data);
        } else if (strcmp(type_input, "CN") == 0) {
            int unique_num;
            Node *find_node = NULL;
            int data = 0;
            scanf(" %d", &unique_num);

            find_node = find_node_with_data(head, unique_num);
            data = delete_node(&head, find_node->next_node);
            printf("%d \n", data);
        } else if (strcmp(type_input, "CP") == 0) {
            int unique_num;
            Node *find_node = NULL;
            int data = 0;
            scanf(" %d", &unique_num);

            find_node = find_node_with_data(head, unique_num);
            data = delete_node(&head, find_node->prev_node);
            printf("%d \n", data);
        }
    }
    return 0;
}