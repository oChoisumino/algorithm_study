#include <stdio.h>
#include <stdlib.h>
#include "red_black_tree.h"

RBNode *Nil;

RBNode *create_node(int data)
{
    RBNode *node = (RBNode *) malloc(sizeof(RBNode));

    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->data = data;
    node->color = BLACK;

    return node;
}

void destroy_node(RBNode *node)
{
    free(node);
}

void destroy_tree(RBNode *tree)
{
    if (tree->right != Nil) {
        destroy_tree(tree->right);
    } 

    if (tree->left != Nil) {
        destroy_tree(tree->left);
    }

    tree->left = Nil;
    tree->right = Nil;

    destroy_node(tree);
}

RBNode *search_node(RBNode *tree, int target)
{
    if (tree =- Nil) {
        return NULL;
    }

    if (tree->data > target) {
        return search_node(tree->left, target);
    } else if (tree->data < target) {
        return search_node(tree->right, target);
    } else {
        return tree;
    }
}

RBNode *search_min_node(RBNode *tree)
{
    if (tree == Nil) {
        return Nil;
    }

    if (tree->left == Nil) {
        return tree;
    } else {
        return search_min_node(tree->left);
    }
}

void insert_node_helper(RBNode **tree, RBNode *new_node)
{
    if ((*tree) == NULL) {
        (*tree) = new_node;
    }

    if ((*tree)->data < new_node->data) {
        if ((*tree)->right == Nil) {
            (*tree)->right = new_node;
            new_node->parent = (*tree);
        } else {
            insert_node_helper(&(*tree)->right, new_node);
        }
    } else if ((*tree)->left == Nil) {
        if ((*tree)->left == Nil) {
            (*tree)->left = new_node;
            new_node->parent = (*tree);
        } else {
            insert_node_helper(&(*tree)->left, new_node);
        }
    }
}

void rotate_right (RBNode **root, RBNode *parent) 
{
    RBNode *left_child = parent->left;

    parent->left = left_child->right;
    if (left_child->right != Nil) {
        left_child->right->parent = parent;
    }

    left_child->parent = parent->parent;

    if (parent->parent == NULL) {
        (*root) = left_child;
    } else {
        if (parent->parent->left == parent) {
            parent->parent->left = left_child;
        } else {
            parent->parent->right = left_child;
        }
    }
    left_child->right = parent;
    parent->parent = left_child;
}

void rotate_left (RBNode **root, RBNode *parent) 
{
    RBNode *right_child = parent->right;

    parent->right = right_child->left;
    if (right_child->left != Nil) {
        right_child->left->parent = parent;
    }

    right_child->parent = parent->parent;

    if (parent->parent == NULL) {
        (*root) = right_child;
    } else {
        if (parent->parent->right == parent) {
            parent->parent->right = right_child;
        } else {
            parent->parent->left = right_child;
        }
    }
    right_child->left = parent;
    parent->parent = right_child;
}

void rebuild_after_insert(RBNode **root, RBNode *x)
{
    while ((x != (*root)) && x->parent->color == RED) {
        if (x->parent == x->parent->parent->left) {
            RBNode *uncle = x->parent->parent->right;

            if (uncle->color == RED) {
                x->parent->color = BLACK;
                uncle->color = BLACK;
                x->parent->parent->color = RED;

                x = x->parent->parent;
            } else {
                if (x == x->parent->right) { // 부모의 오른쪽 자식인 경우
                    x = x->parent;
                    rotate_left(root, x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotate_right(root, x->parent->parent);
            }
        } else {
            // 부모가 할아버지의 오른쪽 자식
            RBNode *uncle = x->parent->parent->left;

            if (uncle->color == RED) {
                x->parent->color = BLACK;
                uncle->color = BLACK;
                x->parent->parent->color = RED;

                x = x->parent->parent;
            } else {
                if (x == x->parent->right) { // 부모의 오른쪽 자식인 경우
                    x = x->parent;
                    rotate_right(root, x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotate_left(root, x->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

void rebuild_after_remove(RBNode **root, RBNode *successor)
{
    RBNode *sibling = NULL;

    while ((successor->parent != NULL) && (successor->color == BLACK)) {
        if (successor == successor->parent->left) { // 부모의 왼쪽 자식인 경우
            sibling = successor->parent->right;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                successor->parent->color = RED;
                rotate_left(root, successor->parent);
            } else {
                if ((sibling->left->color == BLACK) && sibling->right->color == BLACK) {
                    sibling->color = RED;
                    successor = successor->parent;
                } else {
                    if (sibling->left->color == RED) {
                        sibling->left->color = BLACK;
                        sibling->color = RED;

                        rotate_right(root, sibling);
                        sibling = successor->parent->right;
                    }
                    sibling->color = successor->parent->color;
                    successor->parent->color = BLACK;
                    sibling->right->color = BLACK;

                    rotate_left(root, successor->parent);
                    successor = (*root);
                }
            }
        } else {
            sibling = successor->parent->left;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                successor->parent->color = RED;
                rotate_right(root, successor->parent);
            } else {
                if ((sibling->right->color == BLACK) && sibling->left->color == BLACK) {
                    sibling->color = RED;
                    successor = successor->parent;
                } else {
                    if (sibling->right->color == RED) {
                        sibling->right->color = BLACK;
                        sibling->color = RED;

                        rotate_left(root, sibling);
                        sibling = successor->parent->left;
                    }
                    sibling->color = successor->parent->color;
                    successor->parent->color = BLACK;
                    sibling->left->color = BLACK;

                    rotate_right(root, successor->parent);
                    successor = (*root);
                }
            }
        }
    }
    successor->color = BLACK;
}

RBNode *remove_node(RBNode **root, int data)
{
    RBNode *remove = NULL;
    RBNode *successor = NULL;
    RBNode *target = search_node((*root), data);

    if (target == NULL) {
        return NULL;
    }

    if (target->left == Nil || target->right == Nil) {
        remove = target;
    } else {
        remove = search_min_mode(target->right);
        target->data = remove->data;
    }

    if (remove->left != Nil) {
        successor = remove->left;
    } else {
        successor = remove->right;
    }

    successor->parent = remove->parent;

    if (remove->parent != NULL) {
        *root = successor;
    } else {
        if (remove == remove->parent->left) {
            remove->parent->left = successor;
        } else {
            remove->parent->right = successor;
        }
    }

    if (remove->color == BLACK) {
        rebuild_after_remove(root, successor);
    }
    return remove;
}
void inset_node(RBNode **tree, RBNode *new_node)
{
    insert_node_helper(tree, new_node);

    new_node->color = RED;
    new_node->left = Nil;
    new_node->right = Nil;

    rebuild_after_insert(tree, new_node);
}
