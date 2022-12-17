#include <stdio.h>
#include <stdlib.h>

#include "fibonacci_dp.h"

ULONG default_fibonacci(int n)
{
    if (n == 0) {
        return 0;
    } else if ((n == 1) || (n == 2)) {
        return 1;
    } else {
        return (default_fibonacci(n-2) + default_fibonacci(n-1));
    }
}

ULONG dp_fibonacci(int n)
{
    ULONG result = 0;
    ULONG *result_table = NULL;

    if ((n == 0) || (n == 1)) {
        return n;
    } 

    result_table = (ULONG *) malloc(sizeof(ULONG) * (n+1));

    result_table[0] = 0;
    result_table[1] = 1;

    for (int i = 2; i <= n; i++) {
        result_table[i] = result_table[i-1] + result_table[i-2];
    }
    
    result = result_table[n];

    free(result_table);

    return result;
}

int main(void)
{
    int n = 46;

    ULONG result1, result2;

    result1 = default_fibonacci(n);
    result2 = dp_fibonacci(n);

    printf("%ld %ld\n", result1, result2);

    return 0;
}