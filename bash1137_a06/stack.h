/*
--------------------------------------------------
Project: a6q2
File:    stack.h
Author:  Manahil Bashir
Version: 2025-10-22
--------------------------------------------------
*/
#ifndef STACK_H
#define STACK_H
#include "common.h"

typedef struct stack {
  int length;
  NODE *top;
} STACK;

void push(STACK *sp, NODE *np);
NODE *pop(STACK *sp);
void clean_stack(STACK *sp);

#endif