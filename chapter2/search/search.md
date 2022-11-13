# 탐색
### * 순차 탐색
* 데이터 집합의 처음부터 끝까지 차례대로 모든 요소를 비교해서 데이터를 찾는 탐색
* 순차 탐색은 한쪽 방향으로만 탐색을 수행한다고 해서 데이터를 찾는 탐색이다.
* 전진 이동법 
  - 어느 항목이 한번 탐색되고 나면, 그 항목을 데이터 집합의 가장 앞에 위치시키는 방법 
  - 최근 문서 기능과 같은 원리로 동작
* 전위법
  - 탐색된 항목을 바로 이전 항목과 교환
  - 자주 탐색된 항목을 점진적으로 앞으로 옮긴다.

### * 이진 탐색
* 정렬된 데이터 집합에서 사용할 수 있는 고속 탐색 알고리즘
* 이진 탐색의 반복 횟수 log2 n
* 데이터 집합이 배열인 경우 사용 가능
  - 데이터 집합의 처음과 끝을 알아야 한다.
* C 표준 라이브러리의 이진 탐색 함수 : bsearch()
  void *bsearch (
    const void *key, // 찾고자 하는 목표 값 데이터의 주소
    const void *base, // 데이터 집합 배열의 주소
    size_t num, // 데이터 요소의 개수
    size_t width, // 한 데이터 요소의 크기
    int (__cdec1 *compare) (const void *, const void *) // 비교 함수에 대한 포인터
  )

### * 이진 탐색 트리
* 이진 탐색을 위한 트리
* 왼쪽 노드가 오른쪽 노드보다 작다.
  -> 부모 노드가 중앙 요소이다.
  -> (왼쪽 자식노드는 부모노드보다 작고, 오른쪽 자식 노드는 부모노드보다 크다.)
* 데이터 집합이 배열이여야만 하는 이진탐색의 한계를 극복하기 위한 방법
  - 링크드 리스트로 구현이 가능하다.

### * 레드 블랙 트리
* 규칙
  - 모든 노드는 빨간색 아니면 검은색이다.
  - 루트 노드는 검은색이다.
  - 잎 노드는 검은색이다.
  - 빨간 노드의 자식들은 모두 검은색이다. 
    하지만 검은색 노드의 자식이 빨간색일 필요는 없다.
  - 루트 노드에서 모든 잎 노드 사이에 있는 검은색 노드의 수는 모두 동일하다.
* 회전
  - 회전은 부모-자식 노드의 위치를 바꾸는 연산
  - 우회전 : 왼쪽 자식과 부모의 위치를 교환
  - 좌회전 : 오른쪽 자식과 부모 위치를 교환