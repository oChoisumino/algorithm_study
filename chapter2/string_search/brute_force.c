#include <stdio.h>
#include <stdlib.h>

int brute_force(char *text, int text_size, int start, char *pattern, int pattern_size)
{
    int i, j;

    if (text_size <= 0) {
        return -1;
    } 
    
    if (pattern_size <= 0) {
        return -1;
    }

    for (i = start; i < text_size; i++) {
        if ((text_size - start) < pattern_size) {
            break;
        }
        
        for (j = 0; j < pattern_size; j++) {
            if (text[i+j] != pattern[j]) {
                break;
            }
        }
        if (j >= pattern_size) {
            return i;
        }
    }
    return -1;
}
