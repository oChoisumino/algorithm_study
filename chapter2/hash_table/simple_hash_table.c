#include <stdio.h>
#include <stdlib.h>
#include "simple_hash_table.h"

HashTable *create_hash_table(int table_size)
{
    HashTable *table = (HashTable *) malloc(sizeof(HashTable));

    table->table_size = table_size;
    table->table = (Node *) malloc(sizeof(Node)*table_size);

    return table;
}

void destroy_hash_table(HashTable *hash_table)
{
    free(hash_table->table);
    free(hash_table);
}

int devide_hash(int key, int table_size)
{
    return key % table_size;
}

int hash(char *key, int key_length, int table_size)
{
    int hash_value = 0;

    for(int i = 0; i < key_length; i++) {
        hash_value = (hash_value  << 3) + key[i];
    }
    return hash_value % table_size;
}

void hash_table_set(HashTable *hash_table, int key, int value)
{
    int address = hash(key, hash_table->table_size);

    hash_table->table[address].key = key;
    hash_table->table[address].value = value;
}

int hash_table_get(HashTable *hash_table, int key)
{
    int address = hash(key, hash_table->table_size);
    
    return hash_table->table[address].value;
}

int main(void)
{
    HashTable *hash_table = create_hash_table(193);

    hash_table_set(hash_table, 418, 32114);
    hash_table_set(hash_table, 9, 514);
    hash_table_set(hash_table, 27, 8917);
    hash_table_set(hash_table, 1031, 286);

    printf("key %d, value %d \n", 418, hash_table_get(hash_table, 418));
    printf("key %d, value %d \n", 9, hash_table_get(hash_table, 9));
    printf("key %d, value %d \n", 27, hash_table_get(hash_table, 27));
    printf("key %d, value %d \n", 1031, hash_table_get(hash_table, 1031));

    destroy_hash_table(hash_table);

    return 0;
}