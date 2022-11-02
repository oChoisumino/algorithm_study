# Stack
### * 기본 개념
* FILO(First In Last Out) 또는 LIFO(Last In First Out) 구조로 이루어져 있다.
* 요소의 삽입과 삭제가 자료 구조의 한쪽 끝에서만 이루어지는 것이 특징

### * 주요 기능
* 삽입(push)
* 삭제(pop)

### * 배열을 이용한 스택 구현
* 구현이 간단 
* 동적으로 스택 크기 조절이 어려움
* 생성 초기에 지정한 크기만큼 할당(변화 X), 마지막 노드의 위치를 이용하여 삽입과 제거 연산을 함
* 노드의 위치는 배열의 인덱스를 통해 알 수 있다.

### * 링크드 리스트로 구현하는 스택
* 용량에 제한이 없다.
* 노드는 자신의 위에 위치하는 노드에 대한 포인터를 가지고 있어야 한다.

# 이것만은 알고 갑시다.
### 1. 다음과 같은 스택에서 70을 제거하려면 제거 연산을 모드 몇번 수행해야 할까요?(위에서부터 100, 90, 80, 70, 60)
- 4회

### 2. 우리가 앞에서 만들어본 예제에서는 배열 기반 스택을 용량, 최상위 노드의 위치, 노드 배열 구조체로 표현하였습니다. 이런 구조의 배열 기반 스택의 단점 중 하나는 용량을 조절하기 어렵다는 것입니다. 하지만 불가능한 것은 아니지요. as_push() 를 스택의 용량이 모두 소진되었을 때 현재 용량의 30%만큼을 더 늘리도록 개선하세요.
    void As_Push(ArrayStack *Stack, ElementType Data)
    {
        int position = Stack->Top;

        Stack->Nodes[position].Data = Data;
        Stack->Top++;

        // 여기부터 추가
        if(Stack->Top == (Stack->Capacity - 1)) {
            Stack->Capacity = (int)(Stack->Capacity * 1.3);
            Stack->Nodes = (Node *) realloc(Stack->Nodes, Stack->Capacity);
        }
    } 
}

### 3. 만약 배열 기반 스택 예제 프로그램의 as_push() 함수만 용량이 늘어나도록 수정한다면 스택은 커지기만 하고 줄어들지는 않아 결국에는 메모리를 낭비하는 결과를 만들게 됩니다. 따라서 as_pop() 함수도 실제 사용량이 줄어들면 용량을 줄이도록 개선해야 합니다. as_pop() 함수를 사용량이 스택 용량의 70% 미만으로 내려가면 용량을 줄이도록 수정하세요.
ElememtType as_pop(ArrayStack *stack)
{
    int position = --(stack->Top);
    // 이부분 추가
    if (stack->Top < (0.7 * stack->Capacity)) {
        Stack->Capacity = (int)(Stack->Capacity * 0.7);
        Stack->Nodes = (Node *) realloc(Stack->Nodes, Stack->Capacity);
    }
    return Stack->Nodes[position].Data;
}