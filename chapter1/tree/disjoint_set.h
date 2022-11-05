#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

typedef struct _DisjointSet {
    struct _DisjointSet *parent;
    void *data;
} DisjointSet;

#endif //DISJOINT_SET_H
