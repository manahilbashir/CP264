/*
--------------------------------------------------
Project: a5q1
File:    myrecord_sllist.c
Author:  Manahil Bashir
Version: 2025-10-22
--------------------------------------------------
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myrecord_sllist.h"


NODE *sll_search(SLL *sllp, char *name) {
    NODE *ptr = sllp->start;
    while (ptr != NULL) {
        if (strcmp(ptr->data.name, name) == 0) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void sll_insert(SLL *sllp, char *name, float score) {
    // create new node
    NODE *new_node = (NODE *) malloc(sizeof(NODE));
    strcpy(new_node->data.name, name);
    new_node->data.score = score;
    new_node->next = NULL;

    NODE *prev = NULL;
    NODE *curr = sllp->start;

    // find position (sorted by name)
    while (curr != NULL && strcmp(curr->data.name, name) < 0) {
        prev = curr;
        curr = curr->next;
    }

    // insert at head
    if (prev == NULL) {
        new_node->next = sllp->start;
        sllp->start = new_node;
    } else { 
        new_node->next = curr;
        prev->next = new_node;
    }

    sllp->length++;
}

int sll_delete(SLL *sllp, char *name) {
    NODE *prev = NULL;
    NODE *curr = sllp->start;

    while (curr != NULL && strcmp(curr->data.name, name) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        return 0; 
    }

    if (prev == NULL) {
        sllp->start = curr->next; 
    } else {
        prev->next = curr->next;  
    }

    free(curr);
    sllp->length--;
    return 1;
}

void sll_clean(SLL *sllp) {
    NODE *temp, *ptr = sllp->start;
    while (ptr != NULL) {
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
    sllp->start = NULL;
    sllp->length = 0;
}
