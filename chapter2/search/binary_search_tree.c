#include <stdio.h>
#include <stdlib.h>
#include "binary_search_tree.h"

BTNode *create_node(int data)
{
    BTNode *node = (BTNode *) malloc(sizeof(BTNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void destroy_node(BTNode *node)
{
    free(node);
}

BTNode *search_node(BTNode *node, int target)
{
    if (node == NULL) {
        return NULL;
    }
    if (node->data < target) {
        return search_node(node->right, target);
    } else if (node->data > target) {
        return search_node(node->left, target);
    } else {
        return node;
    }
}

void insert_node(BTNode **node, BTNode *new_tree)
{
    if ((*node)->data > new_tree->data) {
        if ((*node)->left == NULL) {
            (*node)->left = new_tree;
        } else {
            insert_node(&((*node)->left), new_tree);
        }
    } else if ((*node)->data < new_tree->data) {
        if ((*node)->right == NULL) {
            (*node)->right = new_tree;
        } else {
            insert_node(&((*node)->right), new_tree);
        }
    } else {

    }
}

BTNode * remove_node(BTNode *tree, BTNode *parent, int target)
{
    BTNode *remove = NULL;

    if (tree == NULL) {
        return NULL;
    }

    if (tree->data > target) {
        remove = remove_node(tree->left, tree, target);
    } else if (tree->data < target) {
        remove = remove_node(tree->right, tree, target);
    } else {
        remove = tree;
        /* 삭제할 노드가 잎노드 인 경우 바로 삭제*/
        if ((remove->left == NULL) && (remove->right == NULL)) {
            if (parent->left == remove) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        } else {
            /* 자식이 양쪽 다 있는 경우*/
            if ((remove->left != NULL) && (remove->right != NULL)) {
                BTNode *replace = remove->right;
                BTNode *replace_parent = NULL;

                // 오른쪽 하위 트리에서 가장 작은 노드로 대체
                while (replace->left != NULL) {
                    replace_parent = replace;
                    replace = replace->left;
                }
                remove->data = replace->data;
                remove = remove_node(replace, replace_parent, replace->data);
                
            } else {
                /* 자식이 한 쪽만 있는 경우*/
                if (remove->left != NULL) {
                    remove->data = remove->left->data;
                    remove = remove_node(remove->left, remove, remove->left->data);
                } else {
                    remove->data = remove->right->data;
                    remove = remove_node(remove->right, remove, remove->right->data);
                }
            }
        }
    }
    return remove;
}
void inorder_print_tree(BTNode *node)
{
    if (node == NULL) {
        return;
    }
    inorder_print_tree(node->left);

    printf("%d ", node->data);

    inorder_print_tree(node->right);
}

void destroy_tree(BTNode *root)
{
    if (root->left != NULL) {
        destroy_tree(root->left);
    }
    if (root->right != NULL) {
        destroy_tree(root->right);
    }
    root->left = NULL;
    root->right = NULL;
    destroy_node(root);
}

int main(void)
{
    BTNode *tree = create_node(123);
    BTNode *node = NULL;

    insert_node(&tree, create_node(22));
    insert_node(&tree, create_node(9918));
    insert_node(&tree, create_node(424));
    insert_node(&tree, create_node(17));
    insert_node(&tree, create_node(3));

    insert_node(&tree, create_node(98));
    insert_node(&tree, create_node(34));

    insert_node(&tree, create_node(760));
    insert_node(&tree, create_node(317));
    insert_node(&tree, create_node(1));

    inorder_print_tree(tree);
    printf("\n");

    printf("removing 98 \n");
    node = remove_node(tree, NULL, 98);
    destroy_node(node);

    inorder_print_tree(tree);
    printf("\n");

    printf("removing 34 \n");
    node = remove_node(tree, NULL, 34);
    destroy_node(node);

    inorder_print_tree(tree);
    printf("\n");

    printf("inserting 111 \n");
    insert_node(&tree, create_node(111));

    inorder_print_tree(tree);
    printf("\n");

    return 0;    
}