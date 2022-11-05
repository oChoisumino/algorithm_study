typedef struct _Node {
    int data;
    struct _Node *prev_node;
    struct _Node *next_node;
}Node ;

Node *create_node(int data);

void destroy_node(Node *node);
void append_tail(Node **head, Node *new_node);
void append_after(Node *list, Node *new_node);

void append_prev(Node *list, Node *new_node);
Node *find_node_with_data(Node *head, int data);

Node *find_node_with_index(Node *head, int index);

void delete_tail(Node **head);
int delete_node(Node **head, Node *node);