#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "making_change.h"

void get_change(int price, int pay, int coin_units[], int change[], int size)
{
    int val = pay - price;
    int cnt = 0;

    while (1) {
        if (val <= 0) {
            break;
        }
        if (cnt == size) {
            break;
        }
        if (val >= coin_units[cnt]) {
            val = val - coin_units[cnt];
            change[cnt]++;
        } else {
            cnt++;
        }
    }
}

void print_change(int coin_units[], int change[], int size)
{
    for (int i = 0; i < size; i++) {
        printf("%8d 원 : %d\n", coin_units[i], change[i]);
    }
}

void sort(int data[], int num) 
{
    for (int i = 0; i < (num-1); i++) {
        int need_sort = 0;
        for (int j = 0; j < (num-1-i); j++) {
            if (data[j] < data[j+1]) {
                int save = data[j];
                data[j] = data[j+1];
                data[j+1] = save;
                need_sort = 1;
            } 
        }

        if (need_sort == 0) {
            break;
        }
    }
}

int main(void)
{
    int cnt = 0;
    int pay = 0, price = 0;
    int unit_count = 0;
    int *coin_units = NULL;
    int *change = NULL;

    printf("동전의 가짓수를 입력하세요 : ");
    scanf("%d", &unit_count);

    coin_units = (int *) malloc(sizeof(int) * unit_count);
    change = (int *) malloc(sizeof(int) * unit_count);

    memset(change, 0, sizeof(int) * unit_count);
    for (int i = 0; i< unit_count; i++) {
        printf("%d번째 동전의 단위를 입력하세요 : ", i);
        scanf("%d", &coin_units[i]);
    }

    sort(coin_units, unit_count);

    printf("물건의 가격을 입력하세요 : ");
    scanf("%d", &price);

    printf("손님이 지불한 돈은 얼마입니까? : ");
    scanf("%d", &pay);

    get_change(price, pay, coin_units, change, unit_count);

    print_change(coin_units, change, unit_count);
    return 0;
}