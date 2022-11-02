#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

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
        node->prev_node = find_node;
    }
}

void append_node(Node **node, Node *new_node)
{
    if (*node == NULL) {
        *node = new_node;
    } else {
        Node *find_node = *node;
        new_node->next_node = find_node->next_node;
        find_node->next_node = new_node;
        new_node->prev_node = find_node;
    }
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

void delete_node(Node **head, Node *node)
{
    if (head == NULL) {
        printf("none of nodes exist in linked list");
    } else {
        Node *find = *head;
        Node *next_node = NULL;
        while(find != NULL) {
            if (find->next_node == node) {
                break;
            }
            find = find->next_node;
        }
        next_node = node->next_node;
        find->next_node = node->next_node;
        next_node->prev_node = find;
        destroy_node(node);

    }
}

static void insert_flow(int num, Node **head) 
{
    int data = 0;
    Node *node = NULL;

    printf("data val : ");
    scanf("%d", &data);

    node = create_node(data);

    if (num == 1) { //insert tail
        append_tail(head, node);
    } else if (num == 2) { // insert with index
        int index = 0;
        Node *find_node = NULL;
        printf("index val : ");
        scanf("%d", &index);

        find_node = find_node_with_index(*head, index);

        append_node(&find_node, node);
    } else if (num == 3) { //insert after the desired data
        int find_data = 0;
        Node *find_node = NULL;

        printf("data val : ");
        scanf("%d", &find_data);

        find_node = find_node_with_data(*head, find_data);

        append_node(&find_node, node);
    } else {
        printf("incorrect input! \n");
    }
}

static void delete_flow(int num, Node **head) 
{
    int data = 0;

    if (num == 1) { //delete tail
        delete_tail(head);
    } else if (num == 2) { // delete with index
        int index = 0;
        Node *find_node = NULL;
        printf("index val : ");
        scanf("%d", &index);

        find_node = find_node_with_index(*head, index);

        delete_node(head, find_node);
    } else if (num == 3) { //insert after the desired data
        int find_data = 0;
        Node *find_node = NULL;

        printf("data val : ");
        scanf("%d", &find_data);

        find_node = find_node_with_data(*head, find_data);

        delete_node(head, find_node);
    } else {
        printf("incorrect input! \n");
    }
}
/*vitamin Quiz : 더블링크드 리스트를 역순으로 출력*/
static void print_nodes(Node *head) {
    Node *node = head;

    if (head == NULL) {
        printf("none of nodes exist");
    }

    while(node->next_node != NULL) {
        node = node->next_node;
    }

    while(node != NULL) {
        printf("data : %d \n", node->data);
        node = node->prev_node;
    }
}

int main(void)
{
    Node *head = NULL;

    while(1) {
    int num = 0;

    printf("1. insert node, 2. delete node 3. print \n");
    printf("Enter another number if you want to quit \n");
    printf("Number : ");
    scanf("%d", &num);
        if (num == 1) {
            printf("1. insert tail \n");
            printf("2. insert with index \n");
            printf("3. insert after the desired data \n");//중복될 경우는 맨 앞 데이터를 기준으로 find
            printf("Number : ");
            scanf("%d", &num);
            insert_flow(num, &head);
        } else if (num == 2) {
            printf("1. delete tail \n");
            printf("2. delete with index \n");
            printf("3. delete after the desired data \n");//중복될 경우는 맨 앞 데이터를 기준으로 find
            printf("Number : ");
            scanf("%d", &num);
            delete_flow(num, &head);
        } else if (num == 3) {
//            Node *node = head;
//            while(node != NULL) {
//                printf("%d === \n", node->data);
//                node = node->next_node;
//            }
            print_nodes(head);
        } else {
            printf("invalid number ... ");
            break;
        }
    }
    return 0;
}