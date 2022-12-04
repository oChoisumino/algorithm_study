#include <stdio.h>
#include "fibonacci.h"

typedef unsigned long ULONG;

typedef struct _matrix_2x2 {
    ULONG data[2][2];
} matrix_2x2;

matrix_2x2 matrix_2x2_multiply(matrix_2x2 a, matrix_2x2 b)
{
    matrix_2x2 c;

    c.data[0][0] = a.data[0][0] * b.data[0][0] + a.data[0][1] * b.data[1][0];
    c.data[0][1] = a.data[0][0] * b.data[0][1] + a.data[0][1] * b.data[1][1];
    c.data[1][0] = a.data[1][0] * b.data[0][0] + a.data[1][1] * b.data[1][0];
    c.data[1][1] = a.data[1][0] * b.data[0][1] + a.data[1][1] * b.data[1][1];

    return c;
}

matrix_2x2 matrix_2x2_power(matrix_2x2 a, int n)
{
    if (n > 1) {
        a = matrix_2x2_power(a, n / 2);
        a = matrix_2x2_multiply(a, a);

        if (n & 1) {
            matrix_2x2 b;
            b.data[0][0] = 1;
            b.data[0][1] = 1;
            b.data[1][0] = 1;
            b.data[1][1] = 0;

            a = matrix_2x2_multiply(a,b);
        }
    }
    return a;
}


ULONG fibonacci(int n)
{
    matrix_2x2 a;

    a.data[0][0] = 1;
    a.data[0][1] = 1;
    a.data[1][0] = 1;
    a.data[1][1] = 0;

    a = matrix_2x2_power(a, n);

    return a.data[0][1];
}

int main(void)
{
    int n = 46;
    ULONG result = fibonacci(n);

    printf("fibonacci %ld \n", result);

    return 0;
}