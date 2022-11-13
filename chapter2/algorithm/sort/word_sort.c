#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN (50)
typedef struct _Data {
    char *str;
    int len;
} Data;

typedef struct _Node {
    Data data;
    struct _Node *next;
} Node;

Node *create_node(char *str)
{
    Node *node = (Node *) malloc(sizeof(Node));
    int len = strlen(str);

    node->data.len = len;
    node->data.str = (char *) malloc(sizeof(char)*(len+1));
    strcpy(node->data.str, str);

    return node;
}

void destroy_node(Node *node)
{
    free(node->data.str);

    free(node);
}

void append_after(Node *node, Node *new_node)
{
    if (new_node == NULL) {
        return;
    }

    if (node != NULL) {
        new_node->next = node->next;
        node->next = new_node;
    }
}

void append_sort(Node **head, Node *new_node)
{
    Node *node = *head;
    Node *prev = NULL;
    if (new_node == NULL) {
        return;
    }
    if (node == NULL) {
        (*head) = new_node;
    } else {
        while(node != NULL) {
            if (node->data.len < new_node->data.len) {
                prev = node;
                node = node->next;
            } else if (node->data.len == new_node->data.len) {
                int compare_val = strcmp(node->data.str, new_node->data.str);

                if (compare_val == 0) { // 동일
                    destroy_node(new_node);
                    return;
                } 
                
                if (compare_val < -1) {
                    prev = node;
                } 
                break;
            } else {
                break;
            }
        }
        if (prev == NULL) { // 맨 앞 삽입
            append_after(new_node, node);
            *head = new_node;
        }
        append_after(prev, new_node);
    }
}

int main(void)
{
    int num = 0;
    Node *head = NULL;
    char str[MAX_STR_LEN] = {0};
    scanf("%d", &num);

    for(int i = 0; i < num; i++) {
        Node *node = NULL;

        memset(str, 0, MAX_STR_LEN);
        scanf("%s", &str[0]);

        node = create_node(&str[0]);
        append_sort(&head, node);
    }
    
    {
        Node *print = head;

        while(print != NULL) {
            printf("%s \n", print->data.str);
            print = print->next;
        }
    }
    return 0;
}