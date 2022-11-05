#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"


BTNode *create_node(ElementType data)
{
    BTNode *node = (BTNode *)malloc(sizeof(BTNode));

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}
void destroy_node(BTNode *node)
{
    free(node);
}

//전위 순회를 응용한 이진 트리 출력
void pre_order_print_tree(BTNode *node)
{
    if (node == NULL) {
        return;
    }
    printf("%c", node->data);
    if (node->left != NULL) {
        pre_order_print_tree(node->left);
    }
    if (node->left != NULL) {
        pre_order_print_tree(node->right);
    }
}

// 중위 순회를 이용한 이진 트리 출력
void in_order_print_tree(BTNode *node)
{
    if (node == NULL) {
        return;
    }
    in_order_print_tree(node->left);

    printf("%c", node->data);

    in_order_print_tree(node->right);
}

// 후위 순회를 응용한 이진 트리 출력
void post_order_print_tree(BTNode *node)
{
    if (node == NULL) {
        return;
    }
    post_order_print_tree(node->left);

    post_order_print_tree(node->right);

    printf("%c", node->data);
}

// 후위 순회를 응용한 트리 소멸
void destroy_tree(BTNode *root)
{
    if (root == NULL) {
        return;
    }
    destroy_tree(root->left);

    destroy_tree(root->right);

    destroy_node(root);
}

int main(void)
{
    BTNode *A = create_node('A');

    BTNode *B = create_node('B');
    BTNode *C = create_node('C');
    BTNode *D = create_node('D');
    BTNode *E = create_node('E');
    BTNode *F = create_node('F');
    BTNode *G = create_node('G');

    A->left = B;
    B->left = C;
    B->right = D;

    A->right = E;
    E->left = F;
    E->right = G;

    printf("preorder ... : ");
    pre_order_print_tree(A);
    printf("\n");

    printf("inorder ... : ");
    in_order_print_tree(A);
    printf("\n");

    printf("postorder ... " );
    post_order_print_tree(A);
    printf("\n");
}