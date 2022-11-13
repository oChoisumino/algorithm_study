#include <stdio.h>
#include <stdlib.h>

long long get_length(int dataset[], int size, int height) 
{   
    long long length = 0;
    for (int i = 0; i < size; i++) {
        if (dataset[i] >= height) {
            length += (dataset[i]-height);
        }
    }
    return length;
}

int main(void)
{
    long long length;
    int tree_num;
    int *tree = NULL;
    int low = 0, high = 0, mid = 0;

    scanf("%d %lld", &tree_num, &length);

    tree = (int *) malloc(sizeof(int)*tree_num);
    //나무의 수 N과 상근이가 집으로 가져가려고 하는 나무의 길이 M
    for (int i = 0; i < tree_num; i++) {
        if (i == (tree_num - 1)) {
            scanf("%d", &tree[i]);
        } else {
            scanf("%d ", &tree[i]);
        }
    }

    // 최대 나무 길이 확인
    for (int i = 0; i < tree_num; i++) {
        if (tree[i] > high) {
            high = tree[i];
        }
   }

    while(low <= high) {
        long long cut_length;

        mid = (low + high) / 2;
        cut_length = get_length(tree, tree_num, mid);
        // get_length(tree, tree_num, mid-1) < cut_length < get_length(tree, tree_num, mid)
        if (cut_length < length) { // 나무가 부족
            high = mid - 1;
        } else if (cut_length == length) {// 나무가 필요한 양과 같은 경우
            break;
        } else { // 나무가 충분한 경우
            if (get_length(tree, tree_num, mid+1) < length) {
                break;
            } else {
                low = mid + 1;
            }
        }
    }
    printf("%d \n", mid);
    
    free(tree);
    return 0;
}
