#include <stdio.h>
#include <stdlib.h>
#include "boyer_moore.h"

static void build_bad_char_table(char *pattern, int pattern_size, int *bad_char_table)
{
    int i, j;

    for (i = 0; i < 128; i++) {
        bad_char_table[i] = -1;
    }

    for (j = 0; j < pattern_size; j++) {
        bad_char_table[pattern[j]] = j;
    }
}

static void build_good_suffix_table(char *pattern, int pattern_size, int *suffix, int *good_suffix_table)
{
    // case1
    int i = pattern_size, j = pattern_size + 1;

    suffix[i] = j;

    while (i > 0) {
        while ((j <= pattern_size) && (pattern[i-1] != pattern[j-1])) {
            if (good_suffix_table[j] == 0) {
                good_suffix_table[j] = j-i;
            }

            j = suffix[j];
        }
        j--;
        i--;

        suffix[i] = j;
    }

    j = suffix[0];

    for (i = 0; i <= pattern_size; i++) {
        if (good_suffix_table[i] == 0) {
            good_suffix_table[i] = j;
        }
        if (i == j) {
            j = suffix[j];
        }
    }
}

static int max(int a, int b)
{
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int boyer_moore(char *text, int text_size, int start, char *pattern, int pattern_size)
{
    int bad_char_table[128];
    int* suffix = (int*)calloc(pattern_size + 1, sizeof(int));
    int* good_suffix_table = (int*)calloc(pattern_size + 1, sizeof(int));
    int i = start, j = 0;

    int position = -1;

    build_bad_char_table(pattern, pattern_size, bad_char_table);
    build_good_suffix_table(pattern, pattern_size, suffix, good_suffix_table);

    while (i <= (text_size - pattern_size)) {
        j = pattern_size - 1;

        while ((j >= 0) && (pattern[j] == text[i+j])) {
            j--;
        }

        if (j < 0) {
            position = i;
            break;
        } else {
            i = i + max(good_suffix_table[j+1], (j - bad_char_table[text[i+j]]));
        }
    }
    free(suffix);
    free(good_suffix_table);

    return position;
}