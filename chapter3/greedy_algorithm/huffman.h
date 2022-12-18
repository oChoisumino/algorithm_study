#ifndef HUFFMAN_H
#define HUFFMAN_H

#define MAX_CHAR 256
#define MAX_BIT 8

typedef unsigned int UINT;
typedef unsigned char UCHAR;

typedef struct _SymbolInfo {
    UCHAR symbol;
    int frequency;
} SymbolInfo;

typedef struct _HuffmanNode
{
    SymbolInfo data;
    struct _HuffmanNode* left;
    struct _HuffmanNode* right;    
} HuffmanNode;

typedef struct _BitBuffer
{
    UCHAR *buffer;
    UINT size;
} BitBuffer;

typedef struct _HuffmanCode
{
    UCHAR code[MAX_BIT];
    int size;
} HuffmanCode;



#endif // HUFFMAN_H