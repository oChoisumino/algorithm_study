#ifndef DLINKED_LIST_INSERTION_SORT_H
#define DLINKED_LIST_INSERTION_SORT_H

typedef struct _DL_Node {
    int data;
    struct _DL_Node *prev;
    struct _DL_Node *next; 
} DL_Node;

#endif // DLINKED_LIST_INSERTION_SORT_H