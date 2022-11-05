#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef char ElementType;

typedef struct _BTNode {
    ElementType data;
    struct _BTNode *left;
    struct _BTNode *right;
} BTNode;

BTNode *create_node(ElementType data);
void destroy_node(BTNode *node);

//전위 순회를 응용한 이진 트리 출력
void pre_order_print_tree(BTNode *node);

// 중위 순회를 이용한 이진 트리 출력
void in_order_print_tree(BTNode *node);

// 후위 순회를 응용한 이진 트리 출력
void post_order_print_tree(BTNode *node);

// 후위 순회를 응용한 트리 소멸
void destroy_tree(BTNode *root);

#endif // BINARY_TREE_H