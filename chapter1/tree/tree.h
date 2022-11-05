#ifndef LEFT_CHILD_RIGHT_SIBLING_H
#define LEFT_CHILD_RIGHT_SIBLING_H

typedef char ElementType;

typedef struct _LCRSNode {
    ElementType data;
    struct _LCRSNode *left_child;
    struct _LCRSNode *right_sibling;
} LCRSNode;

#endif //LEFT_CHILD_RIGHT_SIBLING_H
