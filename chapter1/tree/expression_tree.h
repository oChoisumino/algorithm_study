#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

typedef char ElementType;

typedef struct _ETNode {
    ElementType data;
    struct _ETNode *left;
    struct _ETNode *right;
} ETNode;


#endif // EXPRESSION_TREE_H