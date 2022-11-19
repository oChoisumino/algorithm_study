#ifndef CHAINING_H
#define CHAINING_H


typedef struct _Node {
    char *key;
    char *value;
    struct _Node *next;
} Node;

typedef Node* List;

typedef struct _HashTable {
    List *table;
    int table_size;
} HashTable;

HashTable *create_hash_table(int size);
void destroy_hash_table(HashTable *table);

Node *create_node(char *key, char *value);
void destroy_node(Node *node);

int hash(char *key, int key_len, int table_size);

void hash_table_set(HashTable *hash_table, char *key, char *value);
char *hash_table_get(HashTable *hash_table, char *key);

void destroy_list(List list);

#endif // CHAINING_H