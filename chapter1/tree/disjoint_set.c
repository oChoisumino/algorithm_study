#include <stdio.h>
#include <stdlib.h>
#include "disjoint_set.h"

DisjointSet *find_root(DisjointSet *node)
{
    DisjointSet *find = node;

    while(find->parent != NULL) {
        find = find->parent;
    }
    return find;
}

void union_set(DisjointSet *set1, DisjointSet *set2)
{
    set2 = find_root(set2);
    set2->parent = set1;
}

DisjointSet *make_set(void *data)
{
    DisjointSet *set = (DisjointSet *) malloc(sizeof(DisjointSet));

    set->data = data;
    set->parent = NULL;
}

void distroy_set(DisjointSet *set)
{
    free(set);
}

int main(void)
{
    int a = 1, b = 2, c = 3, d = 4;

    DisjointSet *set1 = make_set(&a);
    DisjointSet *set2 = make_set(&b);
    DisjointSet *set3 = make_set(&c);
    DisjointSet *set4 = make_set(&d);

    printf("Set1 == Set 2 : %d\n", find_root(set1) == find_root(set2));
    union_set(set1, set3);
    union_set(set3, set4);
    printf("Set1 == Set 3 : %d\n", find_root(set1) == find_root(set3));
    printf("Set1 == Set 4 : %d\n", find_root(set1) == find_root(set4));
}