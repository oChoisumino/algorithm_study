#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "karp_rabin.h"


static int hash(char *string, int size)
{
    int val = 0;

    for (int i = 0; i < size; i++) {
        val = val + (int)string[i] * pow(2.0, (size-1-i));
    }
    return val;
}

static int rehash(char *string, int start, int size, int hash_prev)
{
    int val = 0;

    if (start == 0) {
        return hash_prev;
    }
    val = 2 * (hash_prev - (int)string[start-1] * pow(2.0, size-1)) + string[start+size-1];
    
    return val;
}

int karp_rabin(char *text, int text_size, int start, char *pattern, int pattern_size)
{
    int i = 0, j = 0;
    int hash_text, hash_pattern;

    if (text_size <= 0) {
        return -1;
    } 
    
    if (pattern_size <= 0) {
        return -1;
    }

    hash_text = hash(text, pattern_size);
    hash_pattern = hash(pattern, pattern_size);

    for (i = start; i < text_size; i++) {
        if ((text_size - start) < pattern_size) {
            break;
        }
        hash_text = rehash(text, i, pattern_size, hash_text);

        if (hash_pattern == hash_text) {
            for (j = 0; j < pattern_size; j++) {
                if (text[i+j] != pattern[j]) {
                    break;
                }
            }

            if (j >= pattern_size) {
                return i;
            }
        }
    }
    return -1;
}