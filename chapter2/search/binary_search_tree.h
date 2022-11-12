#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

typedef struct _BTNode {
    int data;
    struct _BTNode *left;
    struct _BTNode *right;
} BTNode;

BTNode *create_node(int data);

void destroy_node(BTNode *node);
BTNode *search_node(BTNode *node, int target);

void insert_node(BTNode **node, BTNode *new_tree);
BTNode * remove_node(BTNode *tree, BTNode *parent, int target);
void inorder_print_tree(BTNode *node);
void destroy_tree(BTNode *root);

#endif // BINARY_SEARCH_TREE_H