#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "priority_queue.h"

HuffmanNode *huffman_create_node(SymbolInfo data)
{
    HuffmanNode *new_node = (HuffmanNode *) malloc(sizeof(HuffmanNode));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

void huffman_destroy_node(HuffmanNode *node)
{
    free(node);
}

void huffman_destroy_tree(HuffmanNode *node)
{
    if (node == NULL) {
        return;
    }
    huffman_destroy_node(node->left);
    huffman_destroy_node(node->right);
    huffman_destroy_node(node);
}

void huffman_add_bit(BitBuffer *buffer, char bit)
{
    UCHAR mask = 0x80;

    if (buffer->size % 8 == 0) {
        buffer->buffer = realloc(buffer->buffer, sizeof(UCHAR) * ((buffer->size / 8) + 1));
        buffer->buffer[buffer->size / 8] = 0x00;
    }

    mask >>= buffer->size % 8;

    if (bit == 1) {
        buffer->buffer[buffer->size / 8] |= mask;
    } else {
        buffer->buffer[buffer->size / 8] &= ~mask;
    }
    buffer->size++;
}

void huffman_build_code_table(HuffmanNode *tree, HuffmanCode code_table[MAX_CHAR], UCHAR code[MAX_BIT], int size)
{
    if (tree == NULL) {
        return;
    }

    if (tree->left != NULL) {
        code[size] = 0;
        huffman_build_code_table(tree->left, code_table, code, size + 1);
    }

    if (tree->right != NULL) {
        code[size] = 1;
        huffman_build_code_table(tree->right, code_table, code, size + 1);
    }

    if ((tree->left == NULL) && (tree->right == NULL)) {
        for (int i = 0; i < size; i++) {
            code_table[tree->data.symbol].code[i] = code[i];
        }
        code_table[tree->data.symbol].size = size;
    }
}

void huffman_build_prefix_tree(HuffmanNode **tree, SymbolInfo symbol_info_table[MAX_CHAR])
{
    int i = 0;
    PQNode result;
    PriorityQueue *pq = create_queue(100);

    for (i = 0; i < MAX_CHAR; i++) {
        if (symbol_info_table[i].frequency > 0) {
            HuffmanNode *bit_node = huffman_create_node(symbol_info_table[i]);
            PQNode new_node;

            new_node.data = bit_node;
            new_node.priority = symbol_info_table[i].frequency;

            pq_enqueue(pq, &new_node);
        }
    }

    while (pq->used_size > 1) {
        SymbolInfo new_data = {0,0};
        HuffmanNode *bit_node = huffman_create_node(new_data);
        HuffmanNode *left, *right;

        PQNode pq_left, pq_right, new_node;

        pq_dequeue(pq, &pq_left);
        pq_dequeue(pq, &pq_right);

        left = (HuffmanNode *)pq_left.data;
        right = (HuffmanNode *) pq_right.data;

        bit_node->data.symbol = 0;
        bit_node->data.frequency = left->data.frequency + right->data.frequency;

        bit_node->left = left;
        bit_node->right = right;

        new_node.priority = bit_node->data.frequency;
        new_node.data = bit_node;

        pq_enqueue(pq, &new_node);
    }

    pq_dequeue(pq, &result);
    *tree = (HuffmanNode *)result.data;
}

void huffman_encode(HuffmanNode **tree, UCHAR *source, BitBuffer *encoded, HuffmanCode code_table[MAX_CHAR])
{
    int i = 0, j = 0;
    SymbolInfo symbol_info_table[MAX_CHAR];
    UCHAR temporary[MAX_BIT];

    for (i = 0; i < MAX_CHAR; i++) {
        symbol_info_table[i].symbol = i;
        symbol_info_table[i].frequency = 0;
    }

    i = 0;
    while (source[i] != '\0') {
        symbol_info_table[source[i++]].frequency++;
    }
    huffman_build_prefix_tree(tree, symbol_info_table);
    huffman_build_code_table(*tree, code_table, temporary, 0);
    
    i = 0;
    while (source[i] != '\0') {
        int bit_count = code_table[source[i]].size;

        for (j = 0; j < bit_count; j++) {
            huffman_add_bit(encoded, code_table[source[i]].code[j]);
        }
        i++;
    }
}

void huffman_decode(HuffmanNode *tree, BitBuffer *encoded, UCHAR *decoded)
{
    int i;
    int index = 0;
    HuffmanNode *current = tree;

    for (i = 0; i <= encoded->size; i++) {
        UCHAR mask = 0x80;

        if ((current->left == NULL) && (current->right == NULL)) {
            decoded[index++] = current->data.symbol;
            current = tree;
        }
        
        mask >>= i % 8;

        if ((encoded->buffer[i/8] & mask) != mask) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    decoded[index] = '\0';
}

void huffman_print_binary(BitBuffer *buffer)
{
    for (int i = 0; i < buffer->size; i++) {
        UCHAR mask = 0x80;

        mask >>= i % 8;

        printf("%d", (buffer->buffer[i/8] & mask) == mask);
    }
}

int main(void) 
{
    char *source = "http://www.seanlab.net";
    char *decoded = "";

    HuffmanNode *tree = NULL;
    BitBuffer encoded = {NULL, 0};
    HuffmanCode code_table[MAX_CHAR];

    memset(&code_table, 0, sizeof(HuffmanCode) * MAX_CHAR);

    huffman_encode(&tree, source, &encoded, code_table);

    printf("original size : %ld, encoded size %d\n", ((strlen(source) + 1) * sizeof(char) * 8), encoded.size);

    decoded = (char *) malloc(sizeof(char) * (strlen(source) + 1));

    huffman_decode(tree, &encoded, decoded);

    printf("original : %s\n", source);
    huffman_print_binary(&encoded);
    printf("\n");

    printf("decoded : %s\n", decoded);

    huffman_destroy_tree(tree);
    free(decoded);
    return 0;
}