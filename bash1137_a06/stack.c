/*
--------------------------------------------------
Project: a6q2
File:    stack.c
Author:  Manahil Bashir
Version: 2025-10-22
--------------------------------------------------
*/
#include <stdio.h>
#include "stack.h"

void push(STACK *sp, NODE *np) {
     if (np != NULL) {
        np->next = sp->top;
        sp->top = np;
        sp->length++;
    }
}

NODE *pop(STACK *sp) {
    NODE *np = NULL;

    if (sp->top != NULL) {
        np = sp->top;
        sp->top = sp->top->next;
        np->next = NULL;
        sp->length--;
    }

    return np;
}

void clean_stack(STACK *sp) {
  clean(&(sp->top));
  sp->top = NULL;
  sp->length=0;
}