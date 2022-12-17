#ifndef LONGEST_COMMON_SUBSEQUENCE_H 
#define LONGEST_COMMON_SUBSEQUENCE_H

typedef struct _LCSTable {
    int **data;
} LCSTable;

int default_LCS(char *x, char *y, int i, int j, LCSTable *table);
int dp_LCS(char *x, char *y, int i, int j, LCSTable *table);

void LCS_trace_back(char *x, char *y, int m, int n, LCSTable *table, char *LCS);
void print_table(LCSTable *table, char *x, char *y, int len_x, int len_y);
#endif //LONGEST_COMMON_SUBSEQUENCE_H