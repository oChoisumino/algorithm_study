#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _TreeNode {
    char *data;
    int is_end;
    struct _TreeNode *left_child;
    struct _TreeNode *right_sibling; // 동일한 레벨
} TreeNode;

TreeNode *create_node(char *data)
{
    TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));

    node->data = (char *) malloc(sizeof(char) * (strlen(data)+1));
    memcpy(node->data, data, strlen(data));

    node->left_child = NULL;
    node->right_sibling = NULL;
    node->is_end = 0;
    return node;
}

void destroy_node(TreeNode *node)
{
    if (node != NULL) {
        if (node->data != NULL) {
            free(node->data);
        }
        free(node);
    }
}
TreeNode *add_child_node(TreeNode *parent, TreeNode *child)
{
    if (parent->left_child == NULL) {
        parent->left_child = child;
    } else {
        TreeNode *insert_pos = parent->left_child;
        TreeNode *prev_pos = NULL;

        while (insert_pos != NULL) {
            if (insert_pos->is_end == 1) { 
                if (insert_pos->right_sibling == NULL) { // 마지막 부분인 경우
                    insert_pos->right_sibling = child;
                    return child;
                } else { // 중간인 경우
                    prev_pos = insert_pos;
                    insert_pos = insert_pos->right_sibling;
                    continue;
                }
            } else if (child->is_end == 1) {
                int cmp_val = strcmp(insert_pos->data, child->data);
                if (cmp_val < 0) { // 현재 위치보다 오른쪽에 삽입되어야 하는
                    if (insert_pos->right_sibling == NULL) { // 마지막 부분인 경우
                        insert_pos->right_sibling = child;
                        return child;
                    } else { // 중간인 경우
                        prev_pos = insert_pos;
                        insert_pos = insert_pos->right_sibling;
                    }
                } else { // 현재 위치보다 왼쪽에 삽입되어야 하는 경우
                    if (prev_pos == NULL) { // 맨 앞 삽입인 경우 
                        parent->left_child = child;
                        child->right_sibling = insert_pos;
                    } else { // 중간에 삽입하는 경우
                        child->right_sibling = insert_pos;
                        prev_pos->right_sibling = child;
                    }
                    break;
                }                
            } else {
                int cmp_val = strcmp(insert_pos->data, child->data);
                if (cmp_val == 0) { // 이미 동일한 노드가 있는 경우
                    if (child->data != NULL) {
                        free(child->data);
                    }
                    free(child);
                    return insert_pos;
                } else if (cmp_val < 0) { // 현재 위치보다 오른쪽에 삽입되어야 하는
                    if (insert_pos->right_sibling == NULL) { // 마지막 부분인 경우
                        insert_pos->right_sibling = child;
                        return child;
                    } else { // 중간인 경우
                        prev_pos = insert_pos;
                        insert_pos = insert_pos->right_sibling;
                    }
                } else { // 현재 위치보다 왼쪽에 삽입되어야 하는 경우
                    if (prev_pos == NULL) { // 맨 앞 삽입인 경우 
                        parent->left_child = child;
                        child->right_sibling = insert_pos;
                    } else { // 중간에 삽입하는 경우
                        child->right_sibling = insert_pos;
                        prev_pos->right_sibling = child;
                    }
                    break;
                }
            }
        }
    }
    return child;
}

void destroy_tree(TreeNode *root)
{
    if (root->left_child != NULL) {
        destroy_tree(root->left_child);
    }
    if (root->right_sibling != NULL) {
        destroy_tree(root->right_sibling);
    }
    root->left_child = NULL;
    root->right_sibling = NULL;
    destroy_node(root);
}

void print_tree(TreeNode *node, int depth) 
{
    for(int i = 0; i < depth; i++) {
        printf("--");
    }
    printf("%s\n", node->data);
    
    if (node->left_child != NULL) {
        print_tree(node->left_child, depth+1);
    }
    if (node->right_sibling != NULL) {
        print_tree(node->right_sibling, depth);
    }
}

int main(void)
{
    int n = 0;
    int cnt = 0;
    TreeNode *root = create_node("");
    TreeNode *parent_node = NULL, *new_node = NULL;
    char name[16] = {0};

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        parent_node = root;
        scanf ("%d", &cnt);
        
        for(int j = 0; j < cnt; j++) {
            memset(name, 0, 16);
            scanf(" %s", name);

            new_node = create_node(name);
            if (j == (cnt-1)) {
                new_node->is_end = 1;
            }
            parent_node = add_child_node(parent_node, new_node);
        }
    }
    print_tree(root->left_child, 0);

    destroy_tree(root);
    return 0;
}a