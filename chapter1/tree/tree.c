#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

LCRSNode *create_node(ElementType data)
{
    LCRSNode *node = (LCRSNode *) malloc(sizeof(LCRSNode));
    node->data = data;
    node->left_child = NULL;
    node->right_sibling = NULL;
}

void destroy_node(LCRSNode *node)
{
    free(node);
}

void add_child_node(LCRSNode *parent, LCRSNode *child)
{
    if (parent->left_child == NULL) {
        parent->left_child = child;
    } else {
        LCRSNode *node = parent->left_child;
        while(node->right_sibling != NULL) {
            node = node->right_sibling;
        }
        node->right_sibling = child;
    }
}

void print_tree(LCRSNode *node, int depth) 
{

    for(int i = 0; i < depth; i++) {
        printf(" ");
    }
    printf("%c\n", node->data);
    
    if (node->left_child != NULL) {
        print_tree(node->left_child, depth+1);
    }
    if (node->right_sibling != NULL) {
        print_tree(node->right_sibling, depth);
    }
}

void destroy_tree(LCRSNode *root)
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

/* vitamin quiz : print_nodes_all_level 작성*/
void print_nodes_all_level(LCRSNode *root, int level) {
    LCRSNode *node = root;

    if (level == 0) {
        while(node != NULL) {
            printf("%c\n", node->data);
            node = node->right_sibling;
        }
    } else {
        if (node->left_child != NULL) {
            print_nodes_all_level(node->left_child, level-1);
        }
        if (node->right_sibling != NULL) {
            print_nodes_all_level(node->right_sibling, level);
        }
    }
}

int main(void) 
{
    /*노드 생성*/
    LCRSNode *root = create_node('A');

    LCRSNode *B = create_node('B');
    LCRSNode *C = create_node('C');
    LCRSNode *D = create_node('D');
    LCRSNode *E = create_node('E');
    LCRSNode *F = create_node('F');
    LCRSNode *G = create_node('G');
    LCRSNode *H = create_node('H');
    LCRSNode *I = create_node('I');
    LCRSNode *J = create_node('J');
    LCRSNode *K = create_node('K');

    add_child_node(root, B);
    add_child_node(B, C);
    add_child_node(B, D);
    add_child_node(D, E);
    add_child_node(D, F);
    add_child_node(root, G);
    add_child_node(G, H);
    add_child_node(root, I);
    add_child_node(I, J);
    add_child_node(I, K);
 
    print_nodes_all_level(root, 2);

    destroy_tree(root);
    
    return 0;
}