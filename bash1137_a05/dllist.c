/*
--------------------------------------------------
Project: a5q2
File:    dllist.c
Author:  Manahil Bashir
Version: 2025-10-22
--------------------------------------------------
*/
 
#include <stdio.h>
#include <stdlib.h> 
#include "dllist.h"

NODE *dll_node(char data) {
    NODE *np = (NODE *) malloc(sizeof(NODE));
    if (np != NULL) {
        np->data = data;
        np->prev = NULL;
        np->next = NULL;
    }
    return np;
}

void dll_insert_start(DLL *dllp, NODE *np) {
    if (dllp->start == NULL) { 
        dllp->start = np;
        dllp->end = np;
    } else {
        np->next = dllp->start;
        dllp->start->prev = np;
        dllp->start = np;
    }
    dllp->length++;
}

void dll_insert_end(DLL *dllp, NODE *np) {
    if (dllp->end == NULL) { 
        dllp->start = np;
        dllp->end = np;
    } else {
        dllp->end->next = np;
        np->prev = dllp->end;
        dllp->end = np;
    }
    dllp->length++;
}

void dll_delete_start(DLL *dllp) {
    if (dllp->start != NULL) {
        NODE *temp = dllp->start;
        dllp->start = dllp->start->next;

        if (dllp->start != NULL) {
            dllp->start->prev = NULL;
        } else {
            dllp->end = NULL; 
        }

        free(temp);
        dllp->length--;
    }
}

void dll_delete_end(DLL *dllp) {
    if (dllp->end != NULL) {
        NODE *temp = dllp->end;
        dllp->end = dllp->end->prev;

        if (dllp->end != NULL) {
            dllp->end->next = NULL;
        } else {
            dllp->start = NULL; 
        }

        free(temp);
        dllp->length--;
    }
}

void dll_clean(DLL *dllp) {
    NODE *ptr = dllp->start;
    NODE *temp;

    while (ptr != NULL) {
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }

    dllp->start = NULL;
    dllp->end = NULL;
    dllp->length = 0;
}