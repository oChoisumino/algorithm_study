#include <stdio.h>
#include <stdlib.h>

long long **matrix_multiplication(long long **matrix1, long long **matrix2, int n)
{
    long long **result = NULL;

    result = (long long **) malloc(sizeof(long long*) * n);
    for (int i = 0; i < n; i++){
        result[i] = (long long *) malloc(sizeof(long long) * n);
    }

    for (int h = 0; h < n; h++) {
        for (int w = 0; w < n; w++) {
            result[h][w] = 0;
            for (int w1 = 0; w1 < n; w1++) {
                result[h][w] = matrix1[h][w1] * matrix2[w1][w] + result[h][w];
            }
        }
    }
    return result;
}
void free_matrix(long long **matrix, int n) 
{
    if (matrix != NULL) {
        for (int i = 0; i < n; i++) {
            if (matrix[i] != NULL) {
                free(matrix[i]);
            }
        }
        free(matrix);
    }
}

int main(void)
{
    int n = 0;
    long long square = 0, current_square = 0;
    long long **matrix = NULL;
    long long **result = NULL, **total_result = NULL;

    scanf("%d %lld", &n, &square);
    if ((n < 2) || (n > 5)) {
        return -1;
    } 

    if ((square < 1) || (square > 100000000000)) {
        return -1;
    }

    matrix = (long long **) malloc(sizeof(long long*) * n);
    for (int i = 0; i < n; i++){
        matrix[i] = (long long *) malloc(sizeof(long long) * n);
    }

    for (int h = 0; h < n; h++) {
        for (int w = 0; w < n; w++) {
            if (w == 0) {
                scanf("%lld", &matrix[h][w]);
            } else {
                scanf(" %lld", &matrix[h][w]);
            }
            if (matrix[h][w] > 1000) {
                return 1;
            }
        }
    }
    
    if (square == 1) {
        total_result = matrix;
    } else if (square == 2) {
        total_result = matrix_multiplication(matrix, matrix, n);
    } else {
    }

    while (square > 2) {
        result = matrix_multiplication(matrix, matrix, n);

        for (long long i = 2; i < (square - current_square); i++) {
            if ((square - current_square) > (i * 2)) {
                long long **result_prev = result;

                result = matrix_multiplication(result_prev, result_prev, n);
                free_matrix(result_prev, n);

                i = (i * 2) - 1;
            } else {
                current_square += i;
                if (total_result == NULL) {
                    total_result = result;
                } else {
                    total_result = matrix_multiplication(total_result, result, n);
                    free_matrix(result, n);
                }
                break;
            }
        }

        if ((square - current_square) == 0) {
            break;
        } else if ((square - current_square) == 1) {
            long long **prev = total_result;
            total_result = matrix_multiplication(prev, matrix, n);
            free_matrix(prev, n);
            current_square += 1;
            break;
        } else if ((square - current_square) == 2) {
            long long **prev = total_result;
            long long **matrix_square = matrix_multiplication(matrix, matrix, n);
            total_result = matrix_multiplication(prev, matrix_square, n);
            free_matrix(prev, n);
            free_matrix(matrix_square, n);
            current_square += 2;
            break;
        } else {
            ;
        }
    }

    for (int h = 0; h < n; h++) {
        for (int w = 0; w < n; w++) {
            printf("%lld ", total_result[h][w] % 1000);
        }
        printf("\n");
    }

    return 0;
}