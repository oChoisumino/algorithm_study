#include <stdio.h>
#include <stdlib.h>
#include "kmp_algorithm.h"

static void preprocess(char *pattern, int pattern_size, int *border)
{
    int i = 0, j = -1;

    border[0] = j;

    while (i < pattern_size) {
        while (j > -1 && pattern[i] != pattern[j]) {
            j = border[j];
        }
        i++;
        j++;

        border[i] = j;
    }
}

int knuth_morris_pratt(char *text, int text_size, int start, char *pattern, int pattern_size)
{
    int i = start;
    int j = 0;
    int position = -1;

    int *border = (int *) malloc(sizeof(int) * text_size + 1);

    preprocess(pattern, pattern_size, border);

    while (i < text_size) {
        while (j >= 0 && text[i] != pattern[j]) {
            j = border[j];
        }
        i++;
        j++;

        if (j == pattern_size) {
            position = i - j;
            break;
        }
    }

    free(border);
    return position;
}
