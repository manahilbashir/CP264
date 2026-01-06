/*
--------------------------------------------------
Project: a7q2
File:    bst.c
Author:  Manahil Bashir
Version: 2025-11-05
--------------------------------------------------
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


BSTNODE *bst_node(RECORD data);
BSTNODE *extract_smallest_node(BSTNODE **rootp);


BSTNODE *bst_search(BSTNODE *root, char *key) {
     if (root == NULL)
        return NULL;

    int cmp = strcmp(key, root->data.name);
    if (cmp == 0)
        return root;
    else if (cmp < 0)
        return bst_search(root->left, key);
    else
        return bst_search(root->right, key);
}

void bst_insert(BSTNODE **rootp, RECORD data) {
    if (*rootp == NULL) {
        *rootp = bst_node(data);
    } else {
        int cmp = strcmp(data.name, (*rootp)->data.name);
        if (cmp < 0)
            bst_insert(&((*rootp)->left), data);
        else if (cmp > 0)
            bst_insert(&((*rootp)->right), data);
        else
            (*rootp)->data.score = data.score;  
    }
}

void bst_delete(BSTNODE **rootp, char *key) {
    BSTNODE *root = *rootp;
    if (root == NULL)
        return;

    int cmp = strcmp(key, root->data.name);
    if (cmp < 0)
        bst_delete(&root->left, key);
    else if (cmp > 0)
        bst_delete(&root->right, key);
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            *rootp = NULL;
        } else if (root->left == NULL) {
            BSTNODE *temp = root->right;
            free(root);
            *rootp = temp;
        } else if (root->right == NULL) {
            BSTNODE *temp = root->left;
            free(root);
            *rootp = temp;
        } else {
            BSTNODE *smallest = extract_smallest_node(&root->right);
            root->data = smallest->data;
            free(smallest);
        }
    }
}

BSTNODE *bst_node(RECORD data) {
    BSTNODE *np = (BSTNODE *) malloc(sizeof(BSTNODE));
    if (np) {
        memcpy(&np->data, &data, sizeof(RECORD));
        np->left = NULL;
        np->right = NULL;
    }
    return np;
}

void bst_clean(BSTNODE **rootp) {
    BSTNODE *root = *rootp;
    if (root) {
        if (root->left)
            bst_clean(&root->left);
        if (root->right)
            bst_clean(&root->right);
        free(root);
    }
    *rootp = NULL;
}

BSTNODE *extract_smallest_node(BSTNODE **rootp) {
    BSTNODE *p = *rootp, *parent = NULL;
    if (p) {
        while (p->left) {
            parent = p;
            p = p->left;
        }

        if (parent == NULL)
            *rootp = p->right;
        else
            parent->left = p->right;

        p->left = NULL;
        p->right = NULL;
    }

    return p;
}
