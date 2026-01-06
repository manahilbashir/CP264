/*
 -------------------------------------------------------
 About:    auxiliary queue and stack DS API
 Author:   HBF
 Version:  2025-10-28
 -------------------------------------------------------
 */

#ifndef QUEUE_STACK_H
#define QUEUE_STACK_H

#include "tree.h"

/* ---------- Queue structures ---------- */
typedef struct qnode {
    TNODE *data;
    struct qnode *next;
} QNODE;

typedef struct {
    QNODE *front;
    QNODE *rear;
} QUEUE;

/* ---------- Stack structures ---------- */
typedef struct snode {
    TNODE *data;
    struct snode *next;
} SNODE;

typedef struct {
    SNODE *top;
} STACK;

/* ---------- Queue function prototypes ---------- */
void enqueue(QUEUE *qp, TNODE *node);
TNODE *dequeue(QUEUE *qp);
int is_empty_queue(QUEUE *qp);

/* ---------- Stack function prototypes ---------- */
void push(STACK *sp, TNODE *node);
TNODE *pop(STACK *sp);
int is_empty_stack(STACK *sp);

#endif
