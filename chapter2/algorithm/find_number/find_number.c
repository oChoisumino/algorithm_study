#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash(int key, int table_size)
{
    return (key % table_size);
}

int main(void)
{
    int cnt;
    int table[500] = {0};
    int print_cnt;
    int print_val[100000] = {0};
    scanf("%d", &cnt);

    for (int i = 0; i < cnt; i++) {
        int num = 0, hash_val = 0;
        if (i == 0) {
            scanf("%d", &num);
        } else {
            scanf(" %d", &num);
        }
        num = num + 250;
        hash_val = hash(num, 500);
        table[hash_val] = 1;
    }

    scanf("%d", &print_cnt);

    for (int i = 0; i < print_cnt; i++) {
        int num = 0, hash_val = 0;
        if (i == 0) {
            scanf("%d", &num);
        } else {
            scanf(" %d", &num);
        }
        hash_val = hash(num+250, 500);
        print_val[i] = table[hash_val];
    }
    
    for (int i = 0; i < print_cnt; i++) {
        printf("%d\n", table[i]);
    }
    return 0;
}