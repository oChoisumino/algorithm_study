#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chaining.h"


HashTable *create_hash_table(int size)
{
    HashTable *hash_table = (HashTable *) malloc(sizeof(HashTable));

    hash_table->table_size = size;
    hash_table->table = (List *)malloc(sizeof(List)*size);

    memset(hash_table->table, 0, sizeof(List) * size);
    return hash_table;
}

void destroy_hash_table(HashTable *table)
{
    for (int i = 0; i < table->table_size; i++) {
        destroy_list(table->table[i]);
    }
    free(table->table);
    free(table);
}

Node *create_node(char *key, char *value)
{
    Node *node = (Node *) malloc(sizeof(Node));

    node->key = (char *) malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(node->key, key);
    
    node->value = (char *) malloc(sizeof(char) * (strlen(value) + 1));
    strcpy(node->value, value);

    node->next = NULL;

    return node;
}

void destroy_node(Node *node)
{
    free(node->key);
    free(node->value);
    free(node);
}

int hash(char *key, int key_len, int table_size)
{
    int hash_value = 0;

    for (int i = 0; i < key_len; i++) {
        hash_value = (hash_value << 3) + key[i];
    }
    return (hash_value % table_size);
}

void hash_table_set(HashTable *hash_table, char *key, char *value)
{
    Node *node = create_node(key, value);
    
    int address = hash(key, strlen(key), hash_table->table_size);

    if (hash_table->table[address] == NULL) {
        hash_table->table[address] = node;
    } else {
        node->next = hash_table->table[address];
        hash_table->table[address] = node;
    }
}

char *hash_table_get(HashTable *hash_table, char *key)
{
    int address = hash(key, strlen(key), hash_table->table_size);
    List list = hash_table->table[address];

    if (list == NULL) {
        return NULL;
    }
    while (list != NULL) {
        if (strcmp(list->key, key) == 0) {
            break;
        } else {
            list = list->next;
        }
    }
    
    return list->value;
}

void destroy_list(List list)
{
    List destroy = NULL;
    while(list != NULL) {
        destroy = list;
        list = list->next;
        destroy_node(destroy);
    }
}

int main(void)
{
    HashTable *table = create_hash_table(12289);

    hash_table_set(table, (char *)"MSFT", (char *)"Microsoft Corporation");
    hash_table_set(table, (char *)"JAVA", (char *)"Sun Microsystems");
    hash_table_set(table, (char *)"REDH", (char *)"Red Hat Linux");
    hash_table_set(table, (char *)"APAC", (char *)"Apache Org");
    hash_table_set(table, (char *)"ZYMZZ", (char *)"Unisys Ops Check");
    hash_table_set(table, (char *)"IBM", (char *)"IBM Ltd");
    hash_table_set(table, (char *)"ORCL", (char *)"Oracle Corporation");
    hash_table_set(table, (char *)"CSCO", (char *)"Cisco Systems, Inc.");
    hash_table_set(table, (char *)"GOOG", (char *)"Google Inc.");
    hash_table_set(table, (char *)"YHOO", (char *)"Yahoo! Inc.");
    hash_table_set(table, (char *)"NOVL", (char *)"Novell, Inc.");

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
