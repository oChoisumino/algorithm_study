#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

typedef struct _RBNode {
    struct _RBNode *parent;
    struct _RBNode *left;
    struct _RBNode *right;

    enum { RED, BLACK} color;

    int data;
} RBNode;


int binary_search(int dataset[], int size, int target);

#endif // RED_BLACK_TREE_H