/*
--------------------------------------------------
Project: a7q1
File:    tree.c
Author:  Manahil Bashir
Version: 2025-11-05
--------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "queue_stack.h"
#include "tree.h"


/* Recursive helper for tree_property */
static TPROPS helper_tree_property(TNODE *root) {
    TPROPS prop = {0, 0};
    if (root == NULL)
        return prop;
    
    TPROPS left = helper_tree_property(root->left);
    TPROPS right = helper_tree_property(root->right);

    prop.order = 1 + left.order + right.order;
    prop.height = 1 + ((left.height > right.height) ? left.height : right.height);

    return prop;
}


TPROPS tree_property(TNODE *root) {
    return helper_tree_property(root);

}

void preorder(TNODE *root) {
    if (root) {
        printf("%c ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(TNODE *root) {
    if (root) {
        inorder(root->left);
        printf("%c ", root->data);
        inorder(root->right);
    }
}

void postorder(TNODE *root) {
     if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%c ", root->data);
    }
}

void bforder(TNODE *root) {
    if (root == NULL) return;
    
    QUEUE q = {0};
    enqueue(&q, root);
    TNODE *cur;

    while (!is_empty_queue(&q)) {
        cur = dequeue(&q);
        printf("%c ", cur->data);
        if (cur->left) enqueue(&q, cur->left);
        if (cur->right) enqueue(&q, cur->right);
    }
}

TNODE *bfs(TNODE *root, char val) {
    if (root == NULL) return NULL;

    QUEUE q = {0};
    enqueue(&q, root);
    TNODE *cur;

    while (!is_empty_queue(&q)) {
        cur = dequeue(&q);
        if (cur->data == val)
            return cur;
        if (cur->left) enqueue(&q, cur->left);
        if (cur->right) enqueue(&q, cur->right);
    }
    return NULL;
}

TNODE *dfs(TNODE *root, char val) {
    if (root == NULL) return NULL;

    STACK s = {0};
    push(&s, root);
    TNODE *cur;

    while (!is_empty_stack(&s)) {
        cur = pop(&s);
        if (cur->data == val)
            return cur;
        if (cur->right) push(&s, cur->right);
        if (cur->left) push(&s, cur->left);
    }
    return NULL;
}



// the following functions are given, need to add to your program.

TNODE *tree_node(char val) {
    TNODE *np = (TNODE *) malloc(sizeof(TNODE));
    if (np != NULL) {
        np->data = val;
        np->left = NULL;
        np->right = NULL;
    }
    return np;
}

void clean_tree(TNODE **rootp) {
    TNODE *p = *rootp;
    if (p) {
        if (p->left)
            clean_tree(&p->left);
        if (p->right)
            clean_tree(&p->right);
        free(p);
    }
    *rootp = NULL;
}

void insert_tree(TNODE **rootp, char val) {
    if (*rootp == NULL) {
        *rootp = tree_node(val);
    } else {
        QUEUE queue = { 0 };
        TNODE *p;
        enqueue(&queue, *rootp);
        while (queue.front) {
            p = dequeue(&queue);
            if (p->left == NULL) {
                p->left = tree_node(val);
                break;
            } else {
                enqueue(&queue, p->left);
            }

            if (p->right == NULL) {
                p->right = tree_node(val);
                break;
            } else {
                enqueue(&queue, p->right);
            }
        }
    }
}