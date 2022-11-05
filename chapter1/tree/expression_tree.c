#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expression_tree.h"

ETNode *create_node (ElementType data)
{
    ETNode *node = (ETNode *)malloc(sizeof(ETNode));

    node->data = data;
    node->left = NULL;
    node->right = NULL;
}

void destroy_node(ETNode *node)
{
    free(node);
}

void destroy_tree(ETNode *root)
{
    if (root == NULL) {
        return;
    }
    destroy_tree(root->left);

    destroy_tree(root->right);

    destroy_node(root);
}

void expression_tree(char *postfix, ETNode **node)
{
    int len = strlen(postfix);
    char token = postfix[len-1];
    postfix[len-1] = '\0';

    switch (token)
    {
        case '+':
        case '-':
        case '*':
        case '/':
            *node = create_node(token);
            expression_tree(postfix, &(*node)->right);
            expression_tree(postfix, &(*node)->left);
            break;
        default:
            *node = create_node(token);
            break;
    }
}

double evaluate(ETNode *node)
{
    double left = 0, right = 0, result = 0;

    if (node == NULL) {
        return 0;
    }
    switch(node->data)
    {
        case '+':
            left = evaluate(node->left);
            right = evaluate(node->right);
            result = left + right;
            break;
        case '-':
            left = evaluate(node->left);
            right = evaluate(node->right);
            result = left - right;
            break;
        case '*':
            left = evaluate(node->left);
            right = evaluate(node->right);
            result = left * right;
            break;
        case '/':
            left = evaluate(node->left);
            right = evaluate(node->right);
            result = left / right;
            break;
        default:
            result = (double)(node->data - '0');
            break;
    }
    return result;
}

//전위 순회를 응용한 이진 트리 출력
void pre_order_print_tree(ETNode *node)
{
    if (node == NULL) {
        return;
    }
    printf("%c ", node->data);
    if (node->left != NULL) {
        pre_order_print_tree(node->left);
    }
    if (node->left != NULL) {
        pre_order_print_tree(node->right);
    }
}

// 중위 순회를 이용한 이진 트리 출력
void in_order_print_tree(ETNode *node)
{
    if (node == NULL) {
        return;
    }
    in_order_print_tree(node->left);

    printf("%c ", node->data);

    in_order_print_tree(node->right);
}

// 후위 순회를 응용한 이진 트리 출력
void post_order_print_tree(ETNode *node)
{
    if (node == NULL) {
        return;
    }
    post_order_print_tree(node->left);

    post_order_print_tree(node->right);

    printf("%c ", node->data);
}

int main(void)
{
    char expression[32] = {0};
    ETNode *root = NULL;
    double result = 0;

    scanf("%s", &expression[0]);

    expression_tree(expression, &root);

    result = evaluate(root);
        
    printf("preorder ... : ");
    pre_order_print_tree(root);
    printf("\n");

    printf("inorder ... : ");
    in_order_print_tree(root);
    printf("\n");

    printf("postorder ... " );
    post_order_print_tree(root);
    printf("\n");

    printf("result : %f\n", result);
}