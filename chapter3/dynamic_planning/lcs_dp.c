#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcs_dp.h"

int default_LCS(char *x, char *y, int i, int j, LCSTable *table)
{
    if ((i == 0) || (j == 0)) {
        table->data[i][j] = 0;
    } else if (x[i] == y[j]) {
        table->data[i][j] = default_LCS(x, y, i-1, j-1, table) + 1;
    } else {
        int a = default_LCS(x, y, i-1, j, table);
        int b = default_LCS(x, y, i, j-1, table);

        if (a > b) {
            table->data[i][j] = a;
        } else {
            table->data[i][j] = b;
        }
    }
    return table->data[i][j];
}

int dp_LCS(char *x, char *y, int i, int j, LCSTable *table)
{
    int m = 0;
    int n = 0;

    for (m = 0; m < i; m++) {
        table->data[m][0] = 0;
    }

    for (n = 0; n < j; n++) {
        table->data[0][n] = 0;
    }

    for (m = 1; m <= i; m++) {
        for (n = 1; n <= j; n++) {
            if (x[m-1] == y[n-1]) {
                table->data[m][n] = table->data[m-1][n-1] + 1;
            } else {
                if (table->data[m][n-1] >= table->data[m-1][n]) {
                    table->data[m][n] = table->data[m][n-1];
                } else {
                    table->data[m][n] = table->data[m-1][n];
                }
            }
        }
    }
    return table->data[i][j];
}

void LCS_trace_back(char *x, char *y, int m, int n, LCSTable *table, char *LCS)
{
    if ((m == 0) || (n == 0)) {
        return;
    }

    if ((table->data[m][n] > table->data[m][n-1])  \
      && (table->data[m][n] > table->data[m-1][n]) \
      && (table->data[m][n] > table->data[m-1][n-1])) {
        char temp_lcs[100] = {0};

        strcpy(temp_lcs, LCS);
        sprintf(LCS, "%c%s", x[m-1], temp_lcs);

        LCS_trace_back(x, y, m-1, n-1, table, LCS);
    } else if ((table->data[m][n] > table->data[m-1][n])  \
      && (table->data[m][n] == table->data[m][n-1])) {
        LCS_trace_back(x, y, m, n-1, table, LCS);// 옆으로 이동
    } else {
        LCS_trace_back(x, y, m-1, n, table, LCS); // 위로 이동
    }
}

void print_table(LCSTable *table, char *x, char *y, int len_x, int len_y)
{
    int i = 0, j = 0;

    printf("%4s","");
    
    for (i = 0; i < len_y+1; i++) {
        printf("%c ", y[i]);
    }
    printf("\n");

    for (i = 0; i < len_x+1; i++) {
        if (i == 0) {
            printf("%2s", "");
        } else {
            printf("%-2c", x[i-1]);
        }

        for (j = 0; j < len_y+1; j++) {
            printf("%d ", table->data[i][j]);
        }

        printf("\n");
    }
}

int main(void)
{
    char *x = "GOOD MORNING.";
    char *y = "GUTEN MORGEN.";

    int len_x = strlen(x);
    int len_y = strlen(y);
    int length = 0;
    char *result = NULL;

    LCSTable table = {0};

    table.data = (int **) malloc(sizeof(int*) * (len_x + 1));
    for (int i = 0; i < len_x+1; i++) {
        table.data[i] = (int *) malloc(sizeof(int) * (len_y + 1));

        memset(table.data[i], 0, sizeof(int) * (len_y + 1));
    }

    length = dp_LCS(x, y, len_x, len_y, &table);

    print_table(&table, x, y, len_x, len_y);

    result = (char *) malloc(sizeof(table.data[len_x][len_y] + 1));

    result[0] = '\0';
    
    LCS_trace_back(x, y, len_x, len_y, &table, result);

    printf("\n");

    printf("LCS : %s, length : %d\n", result, length);
    return 0;
}