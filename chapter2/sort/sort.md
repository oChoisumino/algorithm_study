# 정렬 알고리즘
### *기본 개념
* 데이터를 가지런히 나열하는 알고리즘
* 데이터를 빠르고 쉽게 찾을 수 있게 하는 것이 목적
* 종류
  - 버블 정렬
  - 삽입 정렬
  - 퀵 정렬
  
  ### * 버블 정렬
  * 데이터 집합을 순회하면서 집합 내의 이웃 요소들끼리의 교환을 통해 정렬을 수행
  * 데이터 집합을 순회하는 횟수 : n-1
  * 한번 반복할 때 요소 비교 횟수 : 대상의 범위 - 1
  * 총 비교 횟수 : n*(n+1)/2

### * 삽입 정렬
* 데이터 집합을 순회하면서 정렬이 필요한 요소를 뽑아내서 이를 다시 적당한 곳에 삽입해 나가는 알고리즘
* 정렬 대상은 반복 횟수가 늘어날 때마다 1개씩 커진다.
* 삽입 정렬은 데이터 집합이 정렬되어 있는 경우는 비교를 거치지 않는다.

### * 퀵 정렬
* 전체를 공략하는 대신, 전체를 구성하는 구성 요소들을 나누어 공략하는 방법
* 과정
  - 1) 데이터 집합 내에서 임의의 기준 요소를 선택하고, 기준 요소보다 작은 요소들은 왼편, 큰 요소들은 오른편에 위치
  - 2) 나누어진 데이터 집합들을 다시 1)을 반복해서 데이터 집합 분할
  - 3) 더이상 데이터 집합을 나눌 수 없을 때까지 반복
* 배열의 경우 삽입/삭제가 자유롭지 않아, 기준값보다 작은값과 큰값을 교환하는 방식으로 구현

# 이것만은 알고 갑시다.
### 1. 이미 정렬되어 있는 경우, 필요 없는 비교를 수행하지 않고 함수를 종료할 수 있게 BubbleSort를 수정하세요.
    void BubbleSort(int data[], int num) {
        for(int i = 0; i < (num-1); i++) {
            int need_sort = 0;
            for(int j = 0; j < (num-1-i); j++) {
                if (data[j] > data[j+1]) {
                    int save = data[j];
                    data[j] = data[j+1];
                    data[j+1] = save;
                    need_sort = 1;
                } 
            }
            if (need_sort == 0)
                break;
        }
    }

### 2. 더블 링크드 리스트는 탐색이 느린 대신, 데이터 요소의 삽입/삭제가 빠른 자료구조 입니다. 배열을 위해 구현된 InsertionSort() 함수가 더블 링크드 리스트를 정렬할 수 있게 구현하세요.
 double_insertion_sort.c 내 insertion_sort 참고

### 3. QuickSort.c에서 Partition() 가 최악의 값을 피해 기준 요소를 선택하도록 개선하세요.
    int find_index(int dataset[], int left, int right)
    {
        // 중간 값 확인
        int center_index = (left + right) / 2;

        if ((dataset[left] > dataset[right]) && (dataset[right] > dataset[center_index])) {
            return right;
        } else if ((dataset[left] > dataset[center_index]) && (dataset[center_index] > dataset[right])) {
            return center_index;
        } else if ((dataset[center_index] > dataset[left]) && (dataset[left] > dataset[right])) {
            return left;
        } else if ((dataset[center_index] > dataset[right]) && (dataset[right] > dataset[left])) {
            return right;
        } else if ((dataset[right] > dataset[center_index]) && (dataset[center_index] > dataset[left])) {
            return center_index;
        } else {
            return left;
        }
    }
    int partition(int dataset[], int left, int right)
    {
        int first = left;
        int median_index = find_index(dataset, left, right);
        int pivot = dataset[median_index];
                    : 

### 4. QuickSort의 가장 큰 문제점 중 하나는 대용량의 데이터를 처리하기에 부적합하다는 것 입니다. 재귀 호출에 사용되는 스택의 크기 때문이지요. 재귀 호출 되신 순환문을 이용하여 알고리즘을 구현하세요.
    stack_quick_sort.c에 작성