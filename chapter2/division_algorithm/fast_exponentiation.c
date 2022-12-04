#include <stdio.h>
#include "fast_exponentiation.h"

ULONG power(int base, int exponent)
{
    int res = 0;

    if (exponent == 1) {
        return base;
    } else if (exponent == 0) {
        return 1;
    }

    if (exponent % 2 == 0) {
        res = power(base, exponent / 2);
        return res * res;
    } else {
        res = power(base, (exponent - 1) / 2);
        return res * res * base;
    }
}

int main(void)
{
    int base = 2;
    int exponent = 30;


    printf("%d^%d = %lu \n", base, exponent, power(base, exponent));

    return 0;
}
