#ifndef SIMPLE_HASH_TABLE_H
#define SIMPLE_HASH_TABLE_H

typedef struct _Node {
    int key;
    int value;
} Node;

typedef struct _HashTable {
    int table_size;
    Node *table;
} HashTable;

HashTable *create_hash_table(int table_size);
void destroy_hash_table(HashTable *hash_table);
int devide_hash(int key, int table_size);

void hash_table_set(HashTable *hash_table, int key, int value);

int hash_table_get(HashTable *hash_table, int key);

#endif // SIMPLE_HASH_TABLE_H