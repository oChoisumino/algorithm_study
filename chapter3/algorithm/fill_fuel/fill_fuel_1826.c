#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int distance;
    int amount;
    int visited;
} GS_INFO_s;

void sort_distance(GS_INFO_s dataset[], int length) 
{
    for (int i = 1; i < length; i++) {
        GS_INFO_s data = {0};
        if (dataset[i-1].distance < dataset[i].distance) {
            continue;
        }
        data = dataset[i];

        for (int j = 0; j < i; j++) {
            if (data.distance < dataset[j].distance) {
                memcpy(&dataset[j+1], &dataset[j], sizeof(GS_INFO_s)*(i-j));
                dataset[j].distance = data.distance;
                dataset[j].amount = data.amount;
                dataset[j].visited = data.visited;
                break;
            }
        }
    }    
}
void sort_amount(GS_INFO_s dataset[], int length) 
{
    for (int i = 1; i < length; i++) {
        GS_INFO_s data = {0};
        if (dataset[i-1].amount > dataset[i].amount) {
            continue;
        }
        data = dataset[i];

        for (int j = 0; j < i; j++) {
            if (data.amount > dataset[j].amount) {
                memcpy(&dataset[j+1], &dataset[j], sizeof(GS_INFO_s)*(i-j));
                dataset[j].distance = data.distance;
                dataset[j].amount = data.amount;
                dataset[j].visited = data.visited;
                break;
            }
        }
    }    
}

int main(void)
{
    int gas_station_num = 0;
    GS_INFO_s *infos = NULL;
    int distance = 0, amount = 0;
    int res = 0;
    int remain_distance = 0, cur_distance = 0, cur_amount = 0;

    scanf("%d", &gas_station_num);

    infos = (GS_INFO_s *) malloc(sizeof(GS_INFO_s) * gas_station_num);

    for (int i = 0; i < gas_station_num; i++) {
        scanf("%d %d", &infos[i].distance, &infos[i].amount);
        infos[i].visited = 0;
    }

    scanf("%d %d", &distance, &amount);

    sort_distance(infos, gas_station_num);

    cur_amount = amount;
    cur_distance = 0;
    
    for (int i = 0; i < gas_station_num; i++) {
        int able_gas_station = 0;
        int next_distance = 0;

        if (cur_amount >= (distance - cur_distance)) {
            break;
        } else {
            if (infos[i].distance < cur_amount) {
                continue;
            } else {
                sort_amount(infos, i);
                
                for (int j = 0; j <= i; j++) {
                    if (infos[j].visited == 0) {
                        cur_amount = cur_amount + infos[j].amount-infos[j].distance;
                        cur_distance = cur_distance + infos[j].distance;
                        remain_distance = distance - cur_distance;
                        next_distance = infos[i+1].distance - cur_distance;
                        res++;
                        if (next_distance > cur_amount) {
                            continue;
                        } else {
                            break;
                        }
                    }
                }

                if (next_distance > cur_amount) {
                    res = -1;
                    break;
                }
            }
        }
    }

    printf("%d\n", res);
    return 0;
}