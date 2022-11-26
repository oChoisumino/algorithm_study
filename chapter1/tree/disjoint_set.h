#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

typedef struct _DisjointSet {
    struct _DisjointSet *parent;
    void *data;
} DisjointSet;

DisjointSet *find_root(DisjointSet *node);
void union_set(DisjointSet *set1, DisjointSet *set2);
DisjointSet *make_set(void *data);
void distroy_set(DisjointSet *set);

#endif //DISJOINT_SET_H
