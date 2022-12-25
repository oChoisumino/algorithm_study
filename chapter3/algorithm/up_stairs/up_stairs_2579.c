#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stair_result(int stair[], int size)
{
    int *dp = NULL;
    int result = 0;

    if (size == 0) {
        return 0;
    } else if (size == 1) {
        return stair[0];
    } else {
        dp = (int *) malloc(sizeof(int) * (size+1));

        dp[0] = stair[0];;
        dp[1] = stair[1];
        dp[2] = stair[1] + stair[2];
    }

    for (int i = 3; i <= size; i++) {
        if (dp[i-2] + stair[i] > dp[i-3] + stair[i-1] + stair[i]) {
            dp[i] = dp[i-2] + stair[i];
        } else {
            dp[i] = dp[i-3] + stair[i-1] + stair[i];
        }
    }

    result = dp[size];
    free(dp);

    return result;
}

int main(void)
{
    int *stairs = NULL;
    int stair_cnt = 0;

    scanf("%d", &stair_cnt);
    if (stair_cnt > 300) {
        return 1;
    }
    
    stairs = (int *) malloc(sizeof(int) * (stair_cnt + 1));
    stairs[0] = 0;
    for (int i = 1; i <= stair_cnt; i++) {
        scanf("%d", &stairs[i]);
        if (stairs[i] > 10000) {
            return 1;
        }
    }

    printf("%d\n", stair_result(stairs, stair_cnt));

    return 0;
}