
typedef struct _Node {
    char data;
    struct _Node *next_node;
} Node;

typedef struct _LinkedStack {
    Node *head;
    Node *top;
} LinkedStack;



Node * create_node(char data);

void destroy_node(Node *node);

void create_stack(LinkedStack **stack);

void destroy_stack(LinkedStack *stack);

void push_node(LinkedStack *stack, Node *node);

Node *pop_node(LinkedStack *stack);
int is_start_correct (char str);
int stack_capacity(LinkedStack *stack);

int is_num(char c);