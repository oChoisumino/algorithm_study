#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "open_addressing.h"

HashTable *create_hash_table(int size)
{
    HashTable *table = (HashTable *) malloc(sizeof(HashTable));
    table->occupied_cnt = 0;
    table->table_size = size;
    table->table = (ElementType *) malloc(sizeof(ElementType) * size);
}

void clear_element(ElementType *element)
{
    if (element->status == OCCUPIED) {
        free(element->key);
        free(element->value);
    }
}

void destroy_hash_table(HashTable *table)
{
    for (int i = 0; i < table->table_size; i++) {
        clear_element(&table->table[i]);
    }
    free(table->table);
    free(table);
}

void hash_table_set(HashTable **table, char *key, char *value)
{
    int key_len, address, step_size;
    double usage;

    usage = (double) (*table)->occupied_cnt / (*table)->table_size;

    if (usage > 0.5) {
        rehash(table);
    }

    key_len = strlen(key);
    address = hash(key, key_len, (*table)->table_size);
    step_size = hash2(key, key_len, (*table)->table_size);

    while (((*table)->table[address].status != EMPTY) && (strcmp((*table)->table[address].key, key) != 0)) {
        address = (address + step_size) % (*table)->table_size;
    }
    (*table)->table[address].key = (char *) malloc(sizeof(char) * (strlen(key)+1));
    strcpy((*table)->table[address].key, key);
    (*table)->table[address].value = (char *) malloc(sizeof(char) * (strlen(value)+1));
    strcpy((*table)->table[address].value, value);

    (*table)->table[address].status = OCCUPIED;
    (*table)->occupied_cnt++;
}
char *hash_table_get(HashTable *table, char *key)
{
    int address = hash(key, strlen(key), table->table_size);

    while (table->table[address].status == OCCUPIED) {
        if (strcmp(table->table[address].key, key) == 0) {
            break;
        } else {
            int step_size = hash2(key, strlen(key), table->table_size);

            address = (address + step_size) % table->table_size;
        }
    }
    return table->table[address].value;
}

int hash(char *key, int key_len, int table_size)
{
    int hash_value = 0;

    for (int i = 0; i < key_len; i++) {
        hash_value = (hash_value << 3) + key[i];
    }
    hash_value = hash_value % table_size;
    return hash_value;
}

int hash2(char *key, int key_len, int table_size)
{
    int hash_value = 0;

    for (int i = 0; i < key_len; i++) {
        hash_value = (hash_value << 2) + key[i];
    }
    hash_value = hash_value % (table_size - 3);

    return hash_value + 1;
}

void rehash(HashTable **table)
{
    ElementType *OldType = (*table)->table;

    HashTable *new_table = create_hash_table((*table)->table_size * 2);

    for (int i = 0; i < (*table)->table_size; i++) {
        if (OldType->status == OCCUPIED) {
            hash_table_set(&new_table, OldType[i].key, OldType[i].value);
        }
    }
    destroy_hash_table(*table);
    (*table) = new_table;
}

int main(void)
{
    HashTable *table = create_hash_table(12289);

    hash_table_set(&table, (char *)"MSFT", (char *)"Microsoft Corporation");
    hash_table_set(&table, (char *)"JAVA", (char *)"Sun Microsystems");
    hash_table_set(&table, (char *)"REDH", (char *)"Red Hat Linux");
    hash_table_set(&table, (char *)"APAC", (char *)"Apache Org");
    hash_table_set(&table, (char *)"ZYMZZ", (char *)"Unisys Ops Check");
    hash_table_set(&table, (char *)"IBM", (char *)"IBM Ltd");
    hash_table_set(&table, (char *)"ORCL", (char *)"Oracle Corporation");
    hash_table_set(&table, (char *)"CSCO", (char *)"Cisco Systems, Inc.");
    hash_table_set(&table, (char *)"GOOG", (char *)"Google Inc.");
    hash_table_set(&table, (char *)"YHOO", (char *)"Yahoo! Inc.");
    hash_table_set(&table, (char *)"NOVL", (char *)"Novell, Inc.");

    printf("\n");
    printf("key %s, value %s \n", "MSFT", hash_table_get(table, (char *)"MSFT"));
    printf("key %s, value %s \n", "JAVA", hash_table_get(table, (char *)"JAVA"));
    printf("key %s, value %s \n", "REDH", hash_table_get(table, (char *)"REDH"));
    printf("key %s, value %s \n", "APAC", hash_table_get(table, (char *)"APAC"));
    printf("key %s, value %s \n", "ZYMZZ", hash_table_get(table, (char *)"ZYMZZ"));
    printf("key %s, value %s \n", "IBM", hash_table_get(table, (char *)"IBM"));
    printf("key %s, value %s \n", "ORCL", hash_table_get(table, (char *)"ORCL"));
    printf("key %s, value %s \n", "CSCO", hash_table_get(table, (char *)"CSCO"));
    printf("key %s, value %s \n", "GOOG", hash_table_get(table, (char *)"GOOG"));
    printf("key %s, value %s \n", "YHOO", hash_table_get(table, (char *)"YHOO"));
    printf("key %s, value %s \n", "NOVL", hash_table_get(table, (char *)"NOVL"));

    destroy_hash_table(table);

    return 0;
}





