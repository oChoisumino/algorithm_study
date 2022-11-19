#ifndef OPEN_ADDRESSING_H
#define OPEN_ADDRESSING_H

enum ElementStatus {
    EMPTY = 0,
    OCCUPIED = 1
};

typedef struct _ElementType {
    char *key;
    char *value;
    enum ElementStatus status;
} ElementType;

typedef struct _HashTable {
    int table_size;
    int occupied_cnt;
    ElementType *table;
} HashTable;

HashTable *create_hash_table(int size);

void clear_element(ElementType *element);

void destroy_hash_table(HashTable *table);
void hash_table_set(HashTable **table, char *key, char *value);
char *hash_table_get(HashTable *table, char *key);
int hash(char *key, int key_len, int table_size);
int hash2(char *key, int key_len, int table_size);

void rehash(HashTable **table);
#endif // OPEN_ADDRESSING_H